(function ($) {

    $(FormsEngine).on("WorkflowChanged", function (event, data) {

        function getQuerystring(key, default_) {
            if (default_ == null) default_ = "";
            key = key.replace(/[\[]/, "\\\[").replace(/[\]]/, "\\\]");
            var regex = new RegExp("[\\?&]" + key + "=([^&#]*)");
            var qs = regex.exec(window.location.href);
            if (qs == null)
                return default_;
            else
                return qs[1];
        }

        if (!$("body").hasClass("persist-content")) {

            switch (data) {
                case 'START':
                    $(".workflow-container").not("#form-content-container").hide();
                    $("#form-content-container").show();
                    break;
                case 'MANAGEDCHOICE':
                    if ($("#managedchoice-container").text().trim() != '') {
                        $(".workflow-container").hide();

                        //67305-change fadeIn(500) to show() to avoid ManagedChoice container shows after NOMatch container hide() div
                        $("#managedchoice-container").show();
                    }
                    break;
                case 'THANKYOU':
                    if ($("#thankyou-container").text().trim() != '') {
                        $(".workflow-container").hide();
                        $("#thankyou-container").fadeIn(500);
                        $("body").removeClass("responsive-hide-480");
                    }
                    break;
                case 'NOTHANKYOU':
                    if ($("#nothankyou-container").text().trim() != '') {
                        $(".workflow-container").hide();
                        $("#nothankyou-container").fadeIn(500);
                    }
                    break;
                case 'NOMATCH':
                    if ($("#nomatch-container").text().trim() != '') {
                        $(".workflow-container").hide();
                        $("#nomatch-container").fadeIn(500);
                    }
                    if ($("#nomatch-ads-container").text().trim() != '') {
                        //keep the body content on left
                        $("#form-content-container.workflow-container").show();
                        $(".workflow-container").not("#form-content-container").hide();
                        $("#nomatch-ads-container").fadeIn(500);
                    }

                    break;
                default:
                    $(".workflow-container").hide();
                    $(".form-content-container").fadeIn(500);
            }

        }

    });

    var step = 1;

    $(document).ready(function () {

        if (!isNaN(step) && !$('body').hasClass('node-type-blank-slate-page')) {

            $("*[class*= 'show-step-']").hide();
            $(".show-step-" + step).show();

        }
        $('.content .div-program-info').hide();
        //Program changed event with Program information
        FormsEngine.ProgramChangedEvent = function (e) {

            $('.content .div-program-info').show('fast', function () { });
            $('.content .div-program-info .program-name').html(e.ProgramDetails.ProgramName);
            $('.content .div-program-info .program-description').html(e.ProgramDetails.ProgramDescription);

            if (e.ProgramDetails.ProgramDisclaimerType != null) {
                if (e.ProgramDetails.ProgramDisclaimerType == 'link' || e.ProgramDetails.ProgramDisclaimerType == 2) {
                    $('.content .div-program-info .program-disclaimer').addClass('compliance-link');
                    $('.content .div-program-info .compliance-link').html('For program disclosure information, <a target="_blank" href="' + e.ProgramDetails.ProgramDisclaimer + '">click here</a>');
                }
                else if (e.ProgramDetails.ProgramDisclaimerType == 'text' || e.ProgramDetails.ProgramDisclaimerType == 1) {
                    $('.content .div-program-info .program-disclaimer').addClass('compliance-text');
                    $('.content .div-program-info .compliance-text').html(e.ProgramDetails.ProgramDisclaimer);
                }
            } else {
                $('.content .div-program-info .program-disclaimer').html("");
            }

        }
    });

    //Hides/Shows elements per step.
    var lastHash = '';

    function pollHash() {

        if (lastHash !== location.hash) {

            lastHash = location.hash;

            step = lastHash.replace("#_Step", "");

            if (!isNaN(step) && !$('body').hasClass('node-type-blank-slate-page')) {

                $("*[class*= 'show-step-']").hide();
                $(".show-step-" + step).show();

            }// else {

            //    $(".show-step-1").show();

            //}

        }

    }

    setInterval(pollHash, 100);

})(jQuery);