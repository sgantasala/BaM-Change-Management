(function ($) {

    $.fn.leavebehind = function (options) {

        $(this).click(function (e) {

            var $d = $.leavebehind.defaults;

            _set_drupal_settings();

            if ($d.show && $d.leave_behind_url != '') {

                e.preventDefault();

                options = options || {};

                _merge_defaults(options);

                //Redirect to new Tab.
                if ($(this).is('a'))
                    window.open($(this).attr('href'), $d.pop_up_title);
                else
                    window.open($(this).attr('data-new-url'), $d.pop_up_title);

                _set_tracking($d, $(this));

                //Redirect current Window.
                document.location.href = $d.leave_behind_url;

                $.cookie($d.cookie_name, true, {path: '/'});
                $.leavebehind.defaults.show = false;

            }

        });

        return this;

    };

    //Private Methods
    _merge_defaults = function (options) {

        $.each(options, function (k, v) {

            if ($.leavebehind.defaults.hasOwnProperty(k)) {
                $.leavebehind.defaults[k] = options[k];
            }

        });

    }

    _set_show = function () {

        if ($.cookie('_eddy_leave_behind_visited')) {

            $.leavebehind.defaults.show = false;

        }

    }

    _set_drupal_settings = function () {

        if ($.leavebehind.defaults.show && (Drupal != 'undefined' || Drupal != undefined)) {

            if (Drupal.hasOwnProperty('settings')) {

                if (
                    Drupal.settings.hasOwnProperty('eddy_pop_exit_leave_behind_is_active')
                    && Drupal.settings.eddy_pop_exit_leave_behind_is_active
                    && Drupal.settings.hasOwnProperty('eddy_pop_exit_leave_behind_id')
                    && $.leavebehind.defaults.leave_behind_url == '') {

                    $.leavebehind.defaults.leave_behind_url = Drupal.settings.basePath + 'eddy_pop_exit/' + Drupal.settings.eddy_pop_exit_leave_behind_id;

                }

            }

        }

    }

    _set_tracking = function ($d, $t) {

        //Set GA Tracking
        try {

            if (typeof dataLayer != 'undefined') {
                dataLayer.push({
                    "event": "gaEvent",
                    "eventCategory": "leave_behind",
                    "eventAction": "view",
                    "eventValue": $d.leave_behind_url
                });
            }

        } catch (e) { }

        //set EDDY tracking
        try {

            if (typeof _etq != 'undefined') {
                _etq.push(['_etEvent', 'view', $d.leave_behind_url, 'leave_behind']);
            }

        } catch (e) { }

    }

    $.leavebehind = {

        //Initialize Leave Behind.
        init: function (options) {

            //Loads jQuery Cookie if it is undefined.
            if ($.cookie == "undefined" || $.cookie == undefined) {

                $.getScript("https://cdnjs.cloudflare.com/ajax/libs/jquery-cookie/1.4.1/jquery.cookie.js", function () {

                    _set_show();

                });

            } else {

                _set_show();

            }

        },
        defaults: {
            cookie_name: '_eddy_leave_behind_visited',
            current_url: location.href,
            leave_behind_url: '',
            pop_up_title: '',
            show: true
        }

    }

    $(document).ready(function () {

        $.leavebehind.init();

        ////Set anchors to initiate a leave behind.
        // $('a').leavebehind({
            // leave_behind_url: "http://www.elearners.com",
        // });

        $('a').leavebehind();

    });

})(jQuery);