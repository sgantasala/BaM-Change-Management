(function ($) {

    $.ajaxPrefilter(function (options, originalOptions, jqXHR) {

        if (options.url.match(/eddy-listing-ajax/g) != null && options.url.match(/eddy-listing-ajax/g).length > 0 ) {

            plid = 0;

            if (Drupal.settings.hasOwnProperty("plid")) {

                plid = Drupal.settings.plid;

            }

            if (plid > 0) {

                if (options.url.indexOf("?") > 0) {

                    options.url = options.url + "&plid=" + plid;

                } else {

                    options.url = options.url + "?plid=" + plid;

                }

            }

        }

    });

}(jQuery));