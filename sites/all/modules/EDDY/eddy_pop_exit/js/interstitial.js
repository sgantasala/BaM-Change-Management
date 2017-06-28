(function ($) {

    $.interstitial = {

        init: function (options) {

            this.merge_defaults(options);

            this.show_ad(options, function (defaults) {

                if (defaults.show) {
                    var overlay_id = "interstitialwrapper";
                    var html = "<div id=\"" + overlay_id + "\" class=\"pop-up-overlay hide\" style=\"height: 100%;left: 0;filter: alpha(opacity = 70);opacity: 0.7;zoom: 1;position: fixed;top: 0;width: 100%;z-index: 9998;cursor: pointer;overflow:hidden;\"><\/div>";
                    html += "<div id=\"" + defaults.id + "\" class=\"pop-up-holder\" style=\"display:none\"><button class=\"eddy-ad-close\">x</button>";
                    html += options.html;
                    html += "<div id=\"ads_container\">" + defaults.loading_text + "</div>";
                    html += "</div>";

                    $('body').append(html);

                    $("#" + overlay_id).css('background-color', '#ccc');

                    $("#" + defaults.id).css('background', defaults.background);
                    $("#" + defaults.id).css('z-index', defaults.z_index);
                    $("#" + defaults.id).css({ "position": "fixed", "border": "1px solid #333", "text-align": "center" });
                    $("#" + defaults.id).attr('style', $("#" + defaults.id).attr('style') + defaults.box_init_position);
                    $("#" + defaults.id + " .eddy-ad-close").css('color', defaults.button_text_color);
                    $("#" + defaults.id + " .eddy-ad-close").css('background', defaults.button_background);
                    $("#" + defaults.id + " .eddy-ad-close").css({ "position": "absolute", "right": "-5px", "top": "-5px", "border": "1px solid #333", "box-shadow": "none", "font-size": "1.5" });

                    if (defaults.trig_by_click == '' && !defaults.trig_by_step) {

                        $("#" + overlay_id).fadeToggle(defaults.fade_duration);
                        $("#" + defaults.id).delay(defaults.delay).fadeToggle({
                            duration: defaults.fade_duration,
                            complete: function () {
                                if (options.hasOwnProperty('complete')) {
                                    options.complete();
                                }

                            }
                        });
                    } else {

                        if (defaults.trig_by_click != '') {
                            $(defaults.trig_by_click).click(function () {
                                $("#" + overlay_id).fadeToggle(defaults.fade_duration);
                                $("#" + defaults.id).fadeToggle({
                                    duration: defaults.fade_duration,
                                    complete: function () {
                                        if (options.hasOwnProperty('complete')) {
                                            options.complete();
                                        }

                                    }
                                });
                            });
                        } else {
                            $("#" + overlay_id).fadeToggle(defaults.fade_duration);
                            $("#" + defaults.id).fadeToggle({
                                duration: defaults.fade_duration,
                                complete: function () {
                                    if (options.hasOwnProperty('complete')) {

                                        options.complete();
                                    }

                                }
                            });

                        }
                    }

                    $("#" + defaults.id + " .eddy-ad-close").click(function (e) {

                        if (defaults.cookie_expires > 0) {

                            $.cookie(defaults.cookie_name, true, { path: '/', expires: defaults.cookie_expires });

                        } else {

                            $.cookie(defaults.cookie_name, true, { path: '/', });

                        }

                        $("#" + defaults.id + ", #" + overlay_id).fadeToggle(500);

                    });
                }
            });

        },

        defaults: {
            id: 'eddy-interstitial-ad',
            html: '',
            loading_text: 'Loading',
            background: '#999999',
            z_index: '9999',
            button_text_color: 'white',
            button_background: 'red',
            box_init_position: 'width:50%; height:50%; top:25%; left:25%;',
            delay: 1000, //if tri_by_click is '' and trig_by_step is 0, will trig delay
            trig_by_click: '', //using "," to seperate multi targets 
            trig_by_step: false, //for landers only.  
            fade_duration: 500,
            show: false,
            cookie_name: '_eddy_interstitial_ad_closed',
            cookie_expires: 0,

        },

        merge_defaults: function (options) {

            $.each(options, function (k, v) {

                if ($.interstitial.defaults.hasOwnProperty(k)) {
                    $.interstitial.defaults[k] = options[k];
                }

            });

        },

        show_ad: function (options, callback) {

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

            if (typeof callback == "function")
                callback(this.defaults);


        },


    }

})(jQuery);