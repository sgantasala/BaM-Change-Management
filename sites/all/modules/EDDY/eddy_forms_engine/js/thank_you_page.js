(function ($) {
    $(document).ready(function () {

        fe_getProgramTemplateResult(function (data) {

            //var success = "";
            if (data != "") {
                if (typeof JSON === 'object' && typeof JSON.parse === 'function') {
                    var FEResponse = JSON.parse(data);
                }
                else {
                    var FEResponse = $.evalJSON(data);
                }
                success = FEResponse.IsAnyLeadValid;
                set_thankyou_message(FEResponse);
                //set_clicksnet_ads(success);
            }
            if ($.isFunction('set_clicksnet_ads') && $(".ty-page.thank-you-ads").length > 0) {
                setTimeout(function () {
                    set_clicksnet_ads(success);
                }, 300);
            }

        });

        //get cross sell selected programs info
        fe_getSessionObject("ProgramTemplate.UserSelections", function (data) {
            //var Message = "<br/><br/>[UserSelections]";		   
            $("#UserSelections").html(set_crosssell_selected_school(data));

            $('.school-logo').each(function (k, v) {

                var log_path = $(this).attr('data-logo-path');
                var src_name = $(this).closest("li.program-info").find(".school-name").text();

                checkSchoolLogo(log_path, function () {

                    $(v).html('<img src="' + log_path + '"/>');

                }, function () {

                    if (src_name == undefined || src_name == null)
                        src_name = "";

                    $(v).html('<span class="school-logo-name">' + src_name + '</span>');

                });

            });

        });

        //show the pixels on the Thank You page
        fe_loadPixelsForExtProgramTemplateTYPages();


        function set_thankyou_message(FEResponse) {

            //show thank you message from IS

            if (FEResponse.CrossSellThanksYouMessage != "") {
                $('#thank-you-message').html('<h2 class="ty-page">' + FEResponse.CrossSellThanksYouMessage + '</h2>');
            } else {
                //show thank you message from Drupal
                if (FEResponse.IsAnyLeadValid == 'false') {
                    var msg = Drupal.settings.eddy_forms_engine.thank_you_failed_lead_msg;
                    var failed_message = msg.replace("[user-name]", FEResponse.UserFullName);
                    $('#thank-you-message').html(failed_message);
                }
                else {
                    var msg = Drupal.settings.eddy_forms_engine.thank_you_success_lead_msg;
                    var succes_message = msg.replace("[user-name]", FEResponse.UserFullName);
                    $('#thank-you-message').html(succes_message);
                }

            }

        }

        function set_crosssell_selected_school(data) {

            var institution_info = "";

            if (data.length > 0) {
                institution_info += '<ul class="crosssell-school">';

                for (var index = 0; index < data.length; index++) {
                    //institution_info += "<hr>  InstitutionId=" + data[index].InstitutionId;
                    institution_info += '<li class="program-info">';

                    institution_info += '<div data-logo-path="' + data[index].Logo + '" class="school-logo"></div>';
                    institution_info += '<div class="school-name">' + data[index].InstitutionName + '</div>';
                    institution_info += '<div class="program-name">' + data[index].ProgramName + '</div>';
                    institution_info += '</li>';
                }

                institution_info += "</ul>";
            }

            return institution_info;
        }

        function checkSchoolLogo(src, good, bad) {
            var img = new Image();
            img.onload = good;
            img.onerror = bad;
            img.src = src;
        }

    });

})(jQuery);