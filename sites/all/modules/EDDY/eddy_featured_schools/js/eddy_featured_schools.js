(function ($) {
    $(document).ready(function () {
        $(window).on('scroll', function () {
            if ($(this).scrollTop() > 100) {
                $("nav").addClass("top-nav-collapse");

            } else {
                $("nav").removeClass("top-nav-collapse");
            }
        });

        $('.view_institution_website_button').click(function () {
            try {
                if (Drupal.settings.eddy_featured_schools.institutionid != undefined) {
            
                if (typeof dataLayer != 'undefined') {
                    dataLayer.push({
                        "event": "gaEvent",
                        "eventCategory": "nlr",
                        "eventAction": "out-click",
                        "eventLabel": 'Featured School Website Click',
                        "institutionid": Drupal.settings.eddy_featured_schools.institutionid
                    });
                }
            }
        } catch (e) { }
    });


$('.view_program_listing_button').click(function () {
    var urlParamArray = new Array();
    var urlParamString = '';
    if (Drupal.settings.eddy_featured_schools.institutionid != undefined) {
        urlParamArray.push("institution=" + Drupal.settings.eddy_featured_schools.institutionid);
    }
    if (Drupal.settings.eddy_featured_schools.categoryid != undefined) {
        urlParamArray.push("category=" + Drupal.settings.eddy_featured_schools.categoryid);
    }
    if (Drupal.settings.eddy_featured_schools.subjectid != undefined) {
        urlParamArray.push("subject=" + Drupal.settings.eddy_featured_schools.subjectid);
    }
    for (var i = 0; i < urlParamArray.length; i++) {
        if (i == 0) {
            urlParamString += urlParamArray[i];
        } else {
            urlParamString += '&' + urlParamArray[i];
        }
    }
    $("#featured_school_listings_region").load("/eddy-listing-ajax/0/3/10?" + urlParamString);
    $('#program_listing_modal').modal('show');
});
});
})(jQuery);