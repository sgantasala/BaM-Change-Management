(function ($) {

    $(document).ready(function () {

        $('.view_institution_website_button').click(function () {
            try {
                if (Drupal != undefined) {
                    if (Drupal.settings != undefined) {
                        if (Drupal.settings.eddy_blank_slate_page.institutionid != undefined) {

                            if (typeof dataLayer != 'undefined') {
                                dataLayer.push({
                                    "event": "gaEvent",
                                    "eventCategory": "nlr",
                                    "eventAction": "out-click",
                                    "eventLabel": 'Featured School Website Click',
                                    "institutionid": Drupal.settings.eddy_blank_slate_page.institutionid
                                });

                            }
                            if (typeof _etq != 'undefined') {
                                _etq.push(['_etEvent', 'Featured School Website Click', Drupal.settings.eddy_blank_slate_page.institutionid, 'nlr']);
                            }
                        }
                    }
                }
            } catch (e) { }
        });

        $('.view_program_listing_button').click(function () {
            var urlParamArray = new Array();
            var urlParamString = '';
         
            if (Drupal != undefined) {
                if (Drupal.settings != undefined) {
                    if (Drupal.settings.eddy_blank_slate_page.institutionid != undefined) {
                        urlParamArray.push("institution=" + Drupal.settings.eddy_blank_slate_page.institutionid);
                    }
                    if (Drupal.settings.eddy_blank_slate_page.categoryid != undefined) {
                        urlParamArray.push("category=" + Drupal.settings.eddy_blank_slate_page.categoryid);
                    }
                    if (Drupal.settings.eddy_blank_slate_page.subjectid != undefined) {
                        urlParamArray.push("subject=" + Drupal.settings.eddy_blank_slate_page.subjectid);
                    }

                    for (var i = 0; i < urlParamArray.length; i++) {
                        if (i == 0) {
                            urlParamString += urlParamArray[i];
                        } else {
                            urlParamString += '&' + urlParamArray[i];
                        }
                    }
                    $("#school_listings_region").load("/eddy-listing-ajax/0/3/10?" + urlParamString);
                    $('#program_listing_modal').modal('show');
                }
            }
        });
    });
})(jQuery);