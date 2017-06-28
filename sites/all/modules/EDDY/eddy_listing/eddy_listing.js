//Get Query String Param
function getQuerystring(key, default_) {
    if (default_ == null) default_ = "";
    key = key.replace(/[\[]/, "\\\[").replace(/[\]]/, "\\\]");
    var regex = new RegExp("[\\?&]" + key + "=([^&#]*)");
    var qs = regex.exec(window.location.href);
    if (qs == null)
        return default_;
    else
        return qs[1];
}


(function ($) {

    $.updateListings = function (type) {

        function getPathFromUrl(url) {
            if (url.indexOf("?") != -1) {
                return url.split("?")[0];
            } else {
                return url;
            }
        }

        var nid = 0;
        if (Drupal.settings.nid != '')
            nid = Drupal.settings.nid;

        var trailingSlash = '';
        if (Drupal.settings.trailing_slash)
            trailingSlash = '/';

        institutionId = typeof institutionId !== 'undefined' ? institutionId : 0;

        var UserResultsCookieName = "_UserChangeResultsCount";
        var resultsCount = 0;
        var qsParams = new Array();
        var qsParamsString = '';
        var modulefolder = '/sites/all/modules/EDDY/eddy_listing/';

        try {

            if ($.cookie("user_postal_code")) {

                qsParams.postal_code = $.cookie("user_postal_code");

                qsParams.radius = 0;

                if ($.cookie("user_radius"))
                    qsParams.radius = $.cookie("user_radius");

            }

            //var page = getQuerystring("page");

            //if(page > 0){
            //	qsParams.page = page;
            //}

            if (institutionId > 0) {
                qsParams.institution = institutionId;
            }

            var qsCount = 0;

            for (key in qsParams) {
                qsCount++;
                qsParamsString += key + '=' + qsParams[key] + '&';
            }

            if (qsParamsString != "")
                qsParamsString = '?' + qsParamsString.replace(/&+$/, '');

            var currentQS = location.href.split('?')[1];

            if (currentQS != "" && currentQS != undefined && currentQS != 'undefined') {

                if (qsCount > 0) {

                    qsParamsString += "&" + currentQS;

                } else {

                    qsParamsString = "?" + currentQS;

                }

            }

            $(".block-eddy-listing").each(function (i) {

                $(this).before("<p class='listing-loader'>Loading...</p>");

                var elementId = $(this).attr('id');
                var listId = 0;

                listId = elementId.split('-').slice(-1)[0];

                if ($(this).find('.pager').length > 0 && $.cookie(UserResultsCookieName) != null)
                    resultsCount = $.cookie(UserResultsCookieName)
                
                var ajaxUrl = '/eddy-listing-ajax/' + nid + '/' + listId + '/' + resultsCount + trailingSlash + qsParamsString;

                ajaxUrl = $.eddy_core.cache_buster.append_cache_buster_qs(ajaxUrl);

                $.ajax({
                    url: ajaxUrl,
                    context: this,
                    success: function (data) {

                        $(this).find('.content').html(data);
                        $(this).css('visibility', 'visible');
                        $(this).prev('.listing-loader').remove();

                        try {
                            //get campus locations and total result count in json---------------------------
                            if (data != '' && data !== null) {

                                $.view_map();

                            } else {

                                $.initializeMap('map_canvas');
                            }
                        } catch (e) { }

                        if (type == "update") {
                            $(this).addClass("listings-block-updated");
                            $(".listings-block-updated").show();
                        }

                        var loc_href = getPathFromUrl(window.location.href);

                        $('.block-eddy-listing .pager li a, .block-eddy-listing .pager-container li a').each(function () {
                            if ($(this).attr('href') == "")
                                $(this).attr('href', getPathFromUrl(window.location.href));
                        });

                        $('.block-eddy-listing .pager li').each(function () {
                            if ($(this).text().replace(/[^\d]/g, '') != "")
                                $(this).addClass('pager-item-' + $(this).text().replace(/[^\d]/g, ''));
                        });

                        if ($(this).find(".globalProgramResultsCount").length > 0) {
                            $(".pager-count").text($(this).find(".globalProgramResultsCount").val());
                            $(".sponsored-text").show();
                        }
                        else if ($(this).find(".globalResultsCount").length > 0) {
                            $(".pager-count").text($(this).find(".globalResultsCount").val());
                            $(".sponsored-text").show();
                        }
                        else if ($(this).hasClass("main-listings") && !$(this).hasClass("featured-main-listings") && !$("body").hasClass("node-type-school") && $(this).find(".content").html() == "") {

                            $(".pager-count").text("0");

                            if ($("body").hasClass("campus-colleges"))
                                $(this).find(".content").html('<div class="messages warning">Sorry But there Are no Matching Colleges in your location.</div>');
                            else
                                $(this).find(".content").html('<div class="messages warning">Sorry But there Are no Matching Programs in your location.</div>');

                            $(".sponsored-text").hide();
                        }

                        $('.results-count-holder a').each(function () {
                            if ($.cookie(UserResultsCookieName) == $(this).attr("class").split("-").slice(-1)[0]) {
                                $(this).parent("li").addClass("current");
                            }
                            else if ($.cookie(UserResultsCookieName) == null) {
                                $(".results-25").parent("li").addClass("current");
                            }
                        });

                        $(".results-25").click(function (event) {
                            event.preventDefault();
                            $.cookie(UserResultsCookieName, '25', { path: '/', expires: 365 });
                            location.href = location.href;
                        });

                        $(".results-50").click(function (event) {
                            event.preventDefault();
                            $.cookie(UserResultsCookieName, '50', { path: '/', expires: 365 });
                            location.href = location.href.replace("&page=" + getQuerystring("page"), "");
                        });

                        $(".results-100").click(function (event) {
                            event.preventDefault();
                            $.cookie(UserResultsCookieName, '100', { path: '/', expires: 365 });
                            location.href = location.href.replace("&page=" + getQuerystring("page"), "");
                        });


                        //Click Event for Pay for Click Listings
                        $(".eddy-listings a").click(function (e) {

                            if (typeof (SaveClick) == 'function' && $(this).attr("data-track-clicks") == "1") {

                                e.preventDefault();
                                var programProductId = $(this).attr("data-program-product-id");
                                var programId = $(this).attr("data-program-id");
                                var position = $(this).attr("data-position");
                                var listingTypeId = $(this).attr("data-listing-type-id");
                                var pageNumber = $(this).attr("data-page");
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

                        //Get Aggregate Listings
                        $(".view-additional-holder a").click(function (event) {
                            event.preventDefault();

                            var aggrListId = $(this).parent().attr("data-aggregation-list-id");
                            var aggrInstitutionId = $(this).attr("href").replace("#", "");
                            
                            if ($(this).parents('.listing-row').find('.eddy-listings').length == 0) {

                                $(this).html($(this).html() + ' <img class="loader" src="' + modulefolder + 'images/ajax-loader-16-blue.gif" />');
                                
                                var ajaxUrl = '/eddy-listing-ajax/' + nid + '/' + aggrListId + '/' + 100 + trailingSlash + '?institution=' + aggrInstitutionId;
                                ajaxUrl = $.eddy_core.cache_buster.append_cache_buster_qs(ajaxUrl);

                                $.ajax({
                                    url: ajaxUrl,
                                    context: this,
                                    success: function (data) {
                                        $(this).parent().before(data);
                                        $(this).parents('.listing-row').find("li:first").remove();
                                        $(this).parents('.listing-row').find('.eddy-listings').hide().slideDown(500);

                                        $(this).attr("data-original-text", $(this).text());
                                        $(this).find(".loader").remove();
                                        $(this).text("Hide Additional Programs");
                                    }
                                });
                            }
                            else {

                                //Text for View More Link
                                if ($(this).closest('.listing-row').find('.eddy-listings').is(":visible")) {

                                    //Animates User to the top of the listing
                                    var target_offset = $(this).closest(".listing-row").offset();
                                    var target_top = target_offset.top - 10;
                                    $('html, body').animate({ scrollTop: target_top }, 500);

                                    $(this).closest('.listing-row').find('.eddy-listings').delay(800).slideUp(300);
                                    $(this).text($(this).attr("data-original-text"));

                                } else {
                                    $(this).closest('.listing-row').find('.eddy-listings').slideDown(300);
                                    $(this).attr("data-original-text", $(this).text());
                                    $(this).text("Hide Additional Programs");
                                }

                            }


                        });

                        $(".eddy-listings a").click(function (event) {

                            var matchResponseField = $(this).parents(".block-eddy-listing").find(".matchResponseGuid").val();

                            if (matchResponseField.length > 0)
                                $.cookie('_matchingResponseGuid', matchResponseField, { path: '/' });

                        });

                    }

                });

            });

        } catch (e) { }

    }

}(jQuery));



(function ($) {

    $(document).ready(function () {

        $.updateListings("load");

    });

})(jQuery);
