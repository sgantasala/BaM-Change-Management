(function ($) {

    $.toaster = {

        init: function (options) {

            this.merge_defaults(options);
            this.show_toaster_ad(options);

            var defaults = this.defaults;

            if (defaults.show) {

                var id = "#eddy-toaster-ad";

                var html = "<div id=\"eddy-toaster-ad\" style=\"display:none\"><button class=\"close\" id=\"eddy-toaster-ad-button\">x</button>";
                html += options.html;
                html += "</div>";

                $('body').append(html);
                $(id).css('position', 'fixed');
                $(id).css('bottom', '0');
                $(id).css('width', '100%');
                $(id).css('text-align', 'center');
                $(id).css('background', defaults.background);
                $(id).css('padding', defaults.padding);
                $(id).css('z-index', defaults.z_index);
                $('#eddy-toaster-ad-button').css('color', defaults.button_text_color);
                $('#eddy-toaster-ad-button').css('background', defaults.button_background);
                $(id).delay(defaults.delay).slideToggle({
                    duration: defaults.slide_duration,
                    complete: function () {
                        if (options.hasOwnProperty('complete')) {
                            options.complete();
                        }
                    }
                });

                $("#eddy-toaster-ad-button").click(function (e) {

                    if (defaults.cookie_expires > 0) {

                        $.cookie(defaults.cookie_name, true, { path: '/', expires: defaults.cookie_expires });

                    } else {

                        $.cookie(defaults.cookie_name, true, { path: '/', });

                    }

                    $(id).slideToggle(500);

                });

            }

        },

        defaults: {
            background: '#000',
            padding: '10px',
            delay: 1000,
            slide_duration: 1000,
            show: false,
            cookie_name: '_eddy_toaster_ad_closed',
            cookie_expires: 0,
            z_index: '100',
            button_text_color: '#ccc',
            button_background: 'transparent'
        },

        merge_defaults: function (options) {

            $.each(options, function (k, v) {

                if ($.toaster.defaults.hasOwnProperty(k)) {
                    $.toaster.defaults[k] = options[k];
                }

            });

        },

        show_toaster_ad: function (options) {

            //Loads jQuery Cookie if it is undefined.
            if ($.cookie == "undefined" || $.cookie == undefined) {

                $.getScript("https://cdnjs.cloudflare.com/ajax/libs/jquery-cookie/1.4.1/jquery.cookie.js", function () {

                    this.init(options);

                });

            } else {

                if (!$.cookie(this.defaults.cookie_name)) {

                    this.defaults.show = true;

                }

            }

        }

    }

})(jQuery);