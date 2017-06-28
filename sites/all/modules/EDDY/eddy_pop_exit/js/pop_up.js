var exit_pop_up_options = exit_pop_up_options || {};
var exit_pop_up_instance = exit_pop_up_instance || {};

(function ($) {

    $(document).ready(function () {

        exit_pop_up_options = {

            //leavePageMessage: 'This page is asking you to confirm that you want to leave - data you have entered may not be saved.',
            trackIdCookieName: '_CampaignTrackID',
            sessionCookieName: '_Session',
            areasCookieName: 'CategorySubCategorySpecialty',
            mainContentRegion: '.eddy-form-container',
            triggerDeactivationElements: [
                'a',
                '#main',
                'input[type=submit]',
                'button',
                '#managechoice-form-submit-button',
                '#form-nothanks-button-label',
                'select[name=Military_Affiliation]',
                'body'
            ],
            renderTriggerEventType: 'all',//'onmousemove',//'onbeforeunload',
            renderTriggerEventMax_X: 2000,
            renderTriggerEventMin_X: 0,
            renderTriggerEventMax_Y: 10,
            renderTriggerEventMin_Y: 0,
            //excludedUserAgents: 'Android|webOS|iPhone|iPod|windows Phone|BlackBerry|iPad',
            popExitType: 'html_text',
            popExitDelay: 3000,
            outputFullUrl: Drupal.settings.eddy_pop_exit.full_url,
            outputIdLink: Drupal.settings.eddy_pop_exit.id_link,
            basePath: Drupal.settings.basePath,
            availableOnMobile: false,

        };

        exit_pop_up_instance = $.exit_pop_up;
        exit_pop_up_instance.init(exit_pop_up_options);

    });

    $.exit_pop_up = {

        init: function (initOptions) {

            this.get_allow_exit_pops(function (t, show) {

                if (show) {

                    if (initOptions != undefined) {
                        if (Object.keys(initOptions).length) {
                            t.set_current_options(initOptions);
                        }
                    } else {
                        t.set_current_options(t.currentOptions);
                    }
                    setTimeout(function () { t.bind_trigger(); }, t.currentOptions.popExitDelay);

                }

            });

        },
        currentOptions: {
            // Alert Dialog message text that is shown on before unload
            //leavePageMessage: 'This page is asking you to confirm that you want to leave - data you have entered may not be saved.',
            //Track Id Cookie Name
            trackIdCookieName: '_CampaignTrackID',
            //Session Cookie Name
            sessionCookieName: '_Session',
            //Areas Cookie Name
            areasCookieName: 'CategorySubCategorySpecialty',
            //region where the main content exist
            mainContentRegion: '.eddy-form-container',
            //These elements when clicked temporarily disable trigger 
            triggerDeactivationElements: [
                'a',
                '#main',
                'input[type=submit]',
                'button',
                '#managechoice-form-submit-button',
                '#form-nothanks-button-label',
                'select[name=Military_Affiliation]',
                'body'
            ],
            //Events that trigger the pop up
            //onmousemove triggers pop up when mouse is in a predfined area of the screen defined by x and y coordinates
            //onbeforeunload triggers when a user tries to exit the page
            //all uses both onmousemove and onbeforeunload. Pop up is only shown by the first trigger fired
            renderTriggerEventType: 'all',
            //Defines Maximum X axis coordinate of the hot spot that is triggered onmousemove
            renderTriggerEventMax_X: 2000,
            //Defines Minimum X axis coordinate of the hot spot that is triggered onmousemove
            renderTriggerEventMin_X: 10,
            //Defines Maximum Y axis coordinate of the hot spot that is triggered onmousemove
            renderTriggerEventMax_Y: 150,
            //Defines Minimum Y axis coordinate of the hot spot that is triggered onmousemove
            renderTriggerEventMin_Y: 20,
            //this is a list of useragents we do not want the pop up to trigger on
            //excludedUserAgents: 'Android|webOS|iPhone|iPod|windows Phone|BlackBerry|iPad',
            //Type of pop up exit
            popExitType: 'html_text',
            //Iframe source URL
            outputFullUrl: 'http://education-match.com/assets/educationconnection/004/listings-iframe.html?affcamid=1034108&key=AuX8Tvq5on41&clicksnet_study=%5Barea_interest%5D&subid1=www_educationconnection_lp_pop_up&subid2=%5Bsession_id%5D%3A%5Btrack_id%5D',
            //html source URL
            outputIdLink: '/landingpages/eddy_pop_exit/12',
            //base path in relation to where the pop is hosted
            basePath: '/landingpages/',
            //if set to true then it will be available on mobile devices
            availableOnMobile: false,

        },
        has_ad_shown: false,
        get_is_ad_shown: function () {
            var isShown = false;
            isShown = ($.cookie('exit_pop_is_shown')) ? $.cookie('exit_pop_is_shown') : isShown;
            return isShown;
        },
        set_is_ad_shown: function (isShown) {
            isShown = ($.cookie('exit_pop_is_shown', isShown));
        },
        is_frame_loaded: false,
        set_current_options: function (options) {
            $.each(options, function (k, v) {
                if ($.exit_pop_up.currentOptions.hasOwnProperty(k)) {
                    $.exit_pop_up.currentOptions[k] = options[k];
                }
            });
            this.pre_load_creative();
            this.bind_element_events();
            this.bind_trigger_deactivation_elements();
            this.bind_trigger();

        },
        get_allow_exit_pops: function (callback) {

            var t = this;
            var status = false;

            var ajaxUrl = Drupal.settings.eddy_pop_exit_url + '?trackid=' + this.get_current_trackId();

            ajaxUrl = $.eddy_core.cache_buster.append_cache_buster_qs(ajaxUrl);

            $.ajax({
                type: 'GET',
                url: ajaxUrl,
                dataType: 'json',
                success: function (data) {
                    if (data.GetCampaignDetailByTrackIDResult != null) {
                        if (data.GetCampaignDetailByTrackIDResult.hasOwnProperty('AllowExitPops')) {
                            status = data.GetCampaignDetailByTrackIDResult.AllowExitPops;
                            callback(t, status);
                        }
                    }
                },
                error: function () {
                    callback(t, false);
                }
            });
        },
        get_is_ad_rendered: false,
        get_current_trackId: function () {
            var trackId = 'NoTrackId';
            trackId = ($.cookie($.exit_pop_up.currentOptions.trackIdCookieName)) ? $.cookie($.exit_pop_up.currentOptions.trackIdCookieName) : trackId;
            return trackId;
        },
        get_current_session_id: function () {
            var sessionId = 'NoSessionId';
            sessionId = ($.cookie($.exit_pop_up.currentOptions.sessionCookieName)) ? $.cookie($.exit_pop_up.currentOptions.sessionCookieName) : sessionId;
            return sessionId;
        },
        get_areas: function () {
            var areas = null;
            if ($.exit_pop_up.get_areas_cookie_exist()) {
                var cookie = $.cookie($.exit_pop_up.currentOptions.areasCookieName);
                areas = $.parseJSON(cookie);
            }
            return areas;
        },
        get_areas_cookie_exist: function () {
            var doesExist = false;
            if ($.cookie($.exit_pop_up.currentOptions.areasCookieName) && $.cookie($.exit_pop_up.currentOptions.areasCookieName).length > 0) {
                doesExist = true;
            }
            return doesExist;
        },
        get_iframe_output: function () {

            var area = '';
            var output = $.exit_pop_up.currentOptions.outputFullUrl;

            var areas = $.exit_pop_up.get_areas();
            var trackId = $.exit_pop_up.get_current_trackId();
            var sessionId = $.exit_pop_up.get_current_session_id()

            if (areas != null) {

                if (areas.SPECIALTIES && areas.SPECIALTIES.length > 0) {
                    area = encodeURIComponent(areas.SPECIALTIES[0].text);
                } else if (areas.SUBCATEGORIES && areas.SUBCATEGORIES.length > 0) {
                    area = encodeURIComponent(areas.SUBCATEGORIES[0].text);
                } else if (areas.CATEGORIES && areas.CATEGORIES.length > 0) {
                    area = encodeURIComponent(areas.CATEGORIES[0].text);
                } else {
                    area = '';
                }

            } else if (window.name.indexOf("pop_exitarea") > 0 && $.parseJSON(name).pop_exitarea) {
                area = $.parseJSON(name).pop_exitarea;
            }

            output = output.replace('%5Btrack_id%5D', trackId).replace('%5Bsession_id%5D', sessionId).replace('%5Barea_interest%5D', area);

            return output;
        },
        get_html_text_output: function () {
            return $.exit_pop_up.currentOptions.outputIdLink;
        },
        pre_load_creative: function () {
            //preload exit popup layer and our creative
            if ($("#eddy_pop_exit_iframe_wrapper1").length == 0) {

                $('body').append('<div id="eddy_pop_exit_iframe_wrapper1" style="display:none;"></div>');
                $('#eddy_pop_exit_iframe_wrapper1').append('<button id="eddy_pop_exit_iframe_close_btn1">X</button>');

                creative_img = this.currentOptions.basePath + "sites/all/modules/EDDY/eddy_pop_exit/images/exitpopplaceholder.png";
                $('#eddy_pop_exit_iframe_wrapper1').prepend('<div id="eddy_pop_exit_loading"><img src="' + creative_img + '" /></div>');

            }
        },
        check_image: function (src, good, bad) {
            var img = new Image();
            img.onload = good;
            img.onerror = bad;
            img.src = src;
        },
        bind_element_events: function () {
            var parent = this;
            $('#eddy_pop_exit_iframe_close_btn1').live("click", function () {
                jQuery("#eddy_pop_exit_overlay1").fadeOut();
                jQuery("#eddy_pop_exit_iframe_wrapper1").fadeOut();
                parent.unbind_trigger();
            });
            // $($.exit_pop_up.currentOptions.mainContentRegion).mouseleave = this.load_frame_content();
        },
        bind_trigger_deactivation_elements: function () {

            var parent = this;
            $.exit_pop_up.currentOptions.triggerDeactivationElements.forEach(function (element_string) {
                var element = $(element_string);
                if (element.length > 0) {
                    switch (element_string.toLowerCase()) {
                        case 'a':
                            element.live("click", function () {
                                var linkid = $(this).attr('id');
                                var parentclass = $(this).parent().attr('class');
                                if ((linkid != 'next' && linkid != 'prev') || parentclass == 'btnNext buttonLastStep') {
                                    parent.unbind_trigger();
                                }
                            });
                            break;
                        case 'body':
                            if ($.exit_pop_up.currentOptions.renderTriggerEventType.toLowerCase() == 'onbeforeunload') {
                                element.mousemove(function (event) {
                                    if ((event.clientX < 190 && event.clientY < 20) || (event.clientX < 10 && event.clientY < 150)) {
                                        parent.unbind_trigger();
                                    }
                                });
                            }
                            break;
                        default:
                            element.live("click", function () { parent.unbind_trigger(); });
                            break;
                    }
                }
            });
        },
        unbind_trigger: function () {

            window.onbeforeunload = null;
            window.onmousemove = null;

            //switch ($.exit_pop_up.currentOptions.renderTriggerEventType.toLowerCase()) {
            //    case 'onbeforeunload':
            //        window.onbeforeunload = null;
            //        break;
            //    case 'onmousemove':
            //        window.onmousemove = null;
            //        break;
            //    case 'all':
            //        window.onbeforeunload = null;
            //        window.onmousemove = null;
            //        break;

            //}

        },
        bind_trigger: function () {

            window.onbeforeunload = null;
            window.onmousemove = null;

            if (this.currentOptions.availableOnMobile || !(navigator.userAgent.match(/Android|webOS|iPhone|iPod|windows Phone|BlackBerry|iPad/i))) {

                var parent = this;

                switch ($.exit_pop_up.currentOptions.renderTriggerEventType.toLowerCase()) {
                    case 'onbeforeunload':
                        window.onbeforeunload = this.render_on_before_unload;
                        break;
                    case 'onmousemove':
                        $($.exit_pop_up.currentOptions.mainContentRegion).mouseout(function () {
                            window.onmousemove = parent.render_on_mouse_move;
                        });
                        break;
                    case 'all':
                        window.onbeforeunload = this.render_on_before_unload;
                        $($.exit_pop_up.currentOptions.mainContentRegion).mouseout(function () {
                            window.onmousemove = parent.render_on_mouse_move;
                        });
                        break;
                    case 'none':
                        window.onbeforeunload = null;
                        window.onmousemove = null;
                        break;
                }

            }

        },
        iframe: null,

        load_frame_content: function () {

            //if ((!$.exit_pop_up.is_frame_loaded) || (($.exit_pop_up.is_frame_loaded) && ($.exit_pop_up.get_areas_cookie_exist()))) {
            var frameSourceUrl = '';

            switch ($.exit_pop_up.currentOptions.popExitType) {
                case 'html_text':
                    frameSourceUrl = $.exit_pop_up.get_html_text_output();
                    break;
                case 'iframe_add':
                    frameSourceUrl = $.exit_pop_up.get_iframe_output();
                    break;

            }

            if (frameSourceUrl != '') {
                var frame_wrapper = document.getElementById("eddy_pop_exit_iframe_wrapper1");
                if ($('#eddy_pop_exit_iframe1').length > 0) {
                    $(frame_wrapper).find('#eddy_pop_exit_iframe1').remove();
                }
                $.exit_pop_up.iframe = document.createElement("iframe");
                $.exit_pop_up.iframe.id = "eddy_pop_exit_iframe1";
                $.exit_pop_up.iframe.src = frameSourceUrl;
                frame_wrapper.appendChild($.exit_pop_up.iframe);

                $.exit_pop_up.is_frame_loaded = true;
            }
            //}

        },
        render: function () {

            if (!$.exit_pop_up.get_is_ad_shown() && (this.currentOptions.availableOnMobile || !(navigator.userAgent.match(/Android|webOS|iPhone|iPod|windows Phone|BlackBerry|iPad/i)))) {

                document.getElementById('eddy_pop_exit_loading').style.cssText = '';
                document.getElementById('eddy_pop_exit_iframe_wrapper1').style.cssText = '';


                $("#eddy_pop_exit_overlay1").remove();
                if ($("#eddy_pop_exit_overlay1").length == 0) {
                    var overlay_div = document.createElement("div");
                    overlay_div.id = "eddy_pop_exit_overlay1";
                    document.body.appendChild(overlay_div);

                }

                //if ((!$.exit_pop_up.is_frame_loaded) || (($.exit_pop_up.is_frame_loaded) && ($.exit_pop_up.get_areas_cookie_exist()))) {
                this.load_frame_content();
                //}
                $('#eddy_pop_exit_loading').fadeOut();
                $.exit_pop_up.set_is_ad_shown(true);
            }



        },
        render_on_before_unload: function () {
            $.exit_pop_up.render();
            return "This page is asking you to confirm that you want to leave - data you have entered may not be saved.";
        },
        render_on_mouse_move: function (event) {

            if ((event.clientX < $.exit_pop_up.currentOptions.renderTriggerEventMax_X && event.clientY > $.exit_pop_up.currentOptions.renderTriggerEventMin_Y) && (event.clientX > $.exit_pop_up.currentOptions.renderTriggerEventMin_X && event.clientY < $.exit_pop_up.currentOptions.renderTriggerEventMax_Y)) {
                $.exit_pop_up.render();
            }
        }
    }

})(jQuery);