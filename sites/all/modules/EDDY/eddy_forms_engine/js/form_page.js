(function ($) {

    $(document).ready(function () {

        var $imgPath = '/sites/all/modules/EDDY/eddy_forms_engine/images/';

        $('.sidebar-section-link').click(function (event) {

            $(this).next().slideToggle(500);
            var $img = $(this).find('img');
            var $imgSrc = $img.attr('src');

            //if ($imgSrc == $imgPath + 'sidebar-collapse.gif') {
            if ($imgSrc.indexOf("sidebar-collapse") > -1) {
                $img.attr('src', $imgPath + 'sidebar-expand.gif');
                push_tracking_event($(this).attr("id"), "Collapse");
            } else {
                $img.attr('src', $imgPath + 'sidebar-collapse.gif');
                push_tracking_event($(this).attr("id"), "Expand");
            }

            event.preventDefault();

        });

        //Push Track Event Code
        function push_tracking_event(id, event) {

            var eventName = "", schoolName = "Undefined";

            switch (id) {
                case "toggle-program-info-section":
                    eventName = "Program Info";
                    break;
                case "toggle-about-us-section":
                    eventName = "School Info";
                    break;
                case "toggle-accreditation-section":
                    eventName = "Accreditation Info";
                    break;
            }

            if ($("#school-name").length > 0) {
                schoolName = $("#school-name").text();
            }

            if (eventName != "") {
                try { _gaq.push(['_trackEvent', eventName, event, schoolName]); } catch (e) { }
            }

        }

        //Program changed event with Program information
        FormsEngine.ProgramChangedEvent = function (e) {

            $('#div-program-info').show('fast', function () { });
            $('.program-name').html(e.ProgramDetails.ProgramName);

            //responsive program template -- program name
            $("#responsive-school-info .school-info-holder h3").html(e.ProgramDetails.ProgramName);

            $('#program-description').html(e.ProgramDetails.ProgramDescription);

            if (e.ProgramDetails.ProgramDisclaimerType != null) {
                if (e.ProgramDetails.ProgramDisclaimerType == 'link' || e.ProgramDetails.ProgramDisclaimerType == 2) {
                    $('#program-disclaimer').attr('class', 'compliance-link');
                    $('#program-disclaimer').html('For program disclosure information, <a target="_blank" href="' + e.ProgramDetails.ProgramDisclaimer + '">click here</a>');
                }
                else if (e.ProgramDetails.ProgramDisclaimerType == 'text' || e.ProgramDetails.ProgramDisclaimerType == 1) {
                    $('#program-disclaimer').attr('class', 'compliance-text');
                    $('#program-disclaimer').html(e.ProgramDetails.ProgramDisclaimer);
                }
            }

        }

    });

    //replace empty school logo to alt text
    if ($('#column-narrow .school-logo img').length > 0) {
        checkSchoolLogo($('#column-narrow .school-logo img').attr("src"), function () { }, function () {
            $('#column-narrow .school-logo img').replaceWith("<p>" + $('#column-narrow .school-logo img').attr("alt") + "</p>");
        });
    }

})(jQuery);

function checkSchoolLogo(src, good, bad) {
    var img = new Image();
    img.onload = good;
    img.onerror = bad;
    img.src = src;
}