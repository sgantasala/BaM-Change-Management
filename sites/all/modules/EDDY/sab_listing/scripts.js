(function ($) {

    $.ajaxPrefilter(function (options, originalOptions, jqXHR) {

        if (options.url.match(/eddy-listing-ajax/g) != null && options.url.match(/eddy-listing-ajax/g).length > 0 ) {

            program_id = 0;

            if (Drupal.settings.hasOwnProperty("program_id")) {

                program_id = Drupal.settings.program_id;

            }

            if (program_id > 0) {

                if (options.url.indexOf("?") > 0) {

                    options.url = options.url + "&program_id =" + program_id;

                } else {

                    options.url = options.url + "?program_id =" + program_id;

                }

            }

        }

    });

}(jQuery));