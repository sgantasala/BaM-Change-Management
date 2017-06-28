(function ($) {

    $(document).ready(function () {

        //Click Event for Pay for Click Programs
        $(".program-details-page .visit-site a, .program-details-logo a").click(function (e) {

            if (typeof (SaveClick) == 'function' && $(this).attr("data-track-clicks") == "1") {

                e.preventDefault();
                var programProductId = $(this).attr("data-program-product-id");
                var programId = $(this).attr("data-program-id");
                var position = 1;
                var listingTypeId = 1;
                var pageNumber = 1;
                var redirectURL = $(this).attr("data-redirect-url");
                var programName = $(this).attr("data-program-name");

                //Push GTM Event
                try {
                    if (typeof dataLayer != 'undefined') {
                        dataLayer.push({
                            "event": "gaEvent",
                            "eventCategory": "client",
                            "eventAction": "cpc-click",
                            "eventLabel": programId,
                            "programProductId": programProductId,
                            "position": position,
                            "pageNumber": pageNumber,
                        });
                    }
                } catch (e) { }

                //Sets Optimizely Goal.
                if (window.optimizely != undefined) {
                    window['optimizely'].push(["trackEvent", "ad_click_cpc"]);
                }

                //Calls Tracking and redirects user to the correct Click Through URL.
                SaveClick(programProductId, listingTypeId, pageNumber, position, redirectURL);

            }

        });

    });
    
})(jQuery);


function form_wizard_html_completed(data) {
    
    if (data == "NOMATCH") {

        username = ""; 
        if (FormsEngine.hasOwnProperty("UserFullName") && FormsEngine.UserFullName != 'null' && FormsEngine.UserFullName != 'undefined') {
            username = FormsEngine.UserFullName + ", "; 
        }

        jQuery(".eddy-form-wizard-container .form-page-step-message-nomatch").html("<h2><strong>" + username + "Thank you for submitting your information. Unfortunately the program's requirements are not a match.</h2></strong>");
    }
}