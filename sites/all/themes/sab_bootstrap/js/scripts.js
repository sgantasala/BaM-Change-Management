(function ($) {

    $(document).ready(function () {
        //main menu
        //$('.sf-menu li.menuparent > a').on("click", function (e) {
        //    e.preventDefault();
        //});

        //Removes Sub menu from Touch Devices
        //if ('ontouchstart' in document) {
        //    $('.menu li ul li a[href="# "], .menu li ul li a[href="#"]').parent('li').remove();
        //    $(".menu ul ul").remove();
        //    $(".menu ul li.dropdown-submenu a").removeClass('dropdown-toggle').removeAttr("data-toggle").parent('li').removeClass('dropdown-submenu');
        //} else {
        //    $(".menu ul li.dropdown-submenu a").removeAttr("data-toggle");
        //}
        $(window).scroll(function () {

            //hide ads when scroll page only for mobile
            if ($('.logo-container').css("position") == "fixed") {
                var aTop = $('#header-ads').height();
                if ($(this).scrollTop() > 0) {
                    $('#header-ads').hide();
                } else {
                    $('#header-ads').show();
                }
            }
        });

        //add click event on menu for mobile responsive purpose
        $('.faceted-navbar .navbar-nav li > a.dropdown-toggle').on("click", function () {
            $(this).parent().toggleClass('open');
        });

        //program type menu
        $('#block-menu-menu-program-type li').on("click", function () {
            document.location = $(this).find('a').attr("href");
        });

        var country = '#landing_page_filters .faceted-nav-select-wrap.country select';
        if ($(country).val() != '')
            $('#lp-header #country').html($(country + ' option:selected').text());

        var city = '#landing_page_filters .faceted-nav-select-wrap.city select';
        if ($(city).val() != '')
            $('#lp-header #city').html($(city + ' option:selected').text());

        //landing page filters
        $('#sab-landing-page-filters select').change(function () {
            $(this).parents('form').trigger('submit');
        });

        //landing page header  
        rotateTestimonial(0);

        //$('.faceted-nav-select-wrap').click(function () {
        //    $(this).find('select').css('opacity', '1');
        //});


        $('#featured-destination .destination-card').hover(function () {
            $(this).find('.hover-active').css("display", "table");
            }, function () {
                $(this).find('.hover-active').css("display", "none");
            });

        //click any other place then city link, will go to country link
        $('#featured-destination .destination-area').click(function () {
            link = $(this).prev();
            if (link.attr("href").length > 1)
                document.location = link.attr("href");
        });

        $('#block-menu-menu-article-blog-menu .menu > li > a').each(function () {
            if ($(this).attr("title") != '') {
                $('<p>' +$(this).attr("title") + '</p>').insertAfter($(this));
            }
        });

        $('.eddy-listings .view-additional-holder a').live('click', function () {
            if ($(this).prev().hasClass("fa-long-arrow-down")) {
                $(this).prev().removeClass("fa-long-arrow-down").addClass("fa-long-arrow-up");
                $(this).next().removeClass("fa-long-arrow-down").addClass("fa-long-arrow-up");
            } else {
                $(this).prev().removeClass("fa-long-arrow-up").addClass("fa-long-arrow-down");
                $(this).next().removeClass("fa-long-arrow-up").addClass("fa-long-arrow-down");
            }
        });

        var isSafari = /Safari/.test(navigator.userAgent) && /Apple Computer/.test(navigator.vendor);
        //faceted navigation
        $('.faceted-nav-select-wrap select').each(function () {
            //by adding size restict to show scrollbar
            //$(this).attr("size", "5");
            
            $(this).parent().next().val($(this).find("option:selected").text());
            $(this).attr("title", $(this).find("option:selected").text());
            if (isSafari)
                $(this).parent().next().css('width', $(this).width() + 50 + 'px');
            else
                $(this).parent().next().css('width', $(this).width() + 'px');
        });
        $('.faceted-nav-select-wrap select').on("change",function () {
            $(this).parent().next().val($(this).find("option:selected").text());
            $(this).attr("title", $(this).find("option:selected").text());
            //$(this).parent().css('opacity', '0');
        });

        
        filter_search = '';
        obj = '';

        $('.faceted-navbar-container li.dropdown').hover(function () {

            filter_search = '';
        });

        $('.faceted-navbar-container li.dropdown').click(function () {

            filter_search = '';
        });

        //mimic dropdown select instant search start from letter
        $(document).keydown(function (e) {

            if ($('.faceted-navbar-container li.dropdown.open').length > 0) {
                
                var c = e.which;

                if (c >= 65 && c <= 90) {

                    ch = String.fromCharCode(c);

                    if (filter_search != '')
                        filter_search += ch.toLowerCase();
                    else
                        filter_search = ch;

                    $('.faceted-navbar-container li.dropdown.open .dropdown-menu li').each(function () {
                        if ($(this).text().indexOf(filter_search) == 0) {

                            $(this).find('a').focus();

                            return false;
                        }
                    });

                }
            }

        });
        

        resize_event();


        //show right rail
        $("#slideContainer").on("click", function () {
            $('.main-container aside').slideDown("slow");
        });

        //close right rail
        $("#slideClose").on("click", function () {
            $('.main-container aside[role="complementary"]').slideUp("slow");
        });

        $(".navbar-default .navbar-toggle").addClass("collapsed");

        //refresh page to see meanmenu below 768px
        $(window).on("orientationchange", function () {
            location.reload();
        });
        //$(window).on("resize", function () {
        //    location.reload();
        //});
        /* Content Scripts */
        $('#summary-read-more a').live('click', function (e) {
            
            e.preventDefault();

            if ($(this).text() == "Read More") {
                $(this).text("Hide More");


                //67585 -- remove last ... and append hide chunk -- only for mobile, which #extendChunk exists                	            
                if ($('#extendChunk').length > 0) {
                    var myParagraph = $("#summary-body-hidden").prev();
                    myParagraph.html(myParagraph.html().substring(0, myParagraph.html().lastIndexOf('...')));

                    myParagraph.append($('#extendChunk'));
                }

            } else {
                $(this).text("Read More");

                //67585 -- move extendChunk to hide div then add ... at end -- only for mobile, which #extendChunk exists 	            
                if ($('#extendChunk').length > 0) {

                    $("#summary-body-hidden").prepend($('#extendChunk'));
                    $("#summary-body-hidden").prev().html($("#summary-body-hidden").prev().html() + '...');
                }

            }

            $("#summary-body-hidden").slideToggle(400, function () { });

        });

        function resize_event() {

            //<=480px     
            if ($('#header-menu').css("margin-top") != "0px" && $('#header-menu').css("margin-top") <= "65px") {
                $(document).ajaxSuccess(function (event, xhr, settings) {
                    if ($(settings.context).find('.eddy-listings .logo-holder .view-all')) {
                        $(settings.context).find('.eddy-listings .logo-holder .view-all').each(function () {                            
                            $(this).insertBefore($(this).parent().next().find('.programdata .learn-more'));
                        });
                        
                    }
                });

            }
            //<=767px  
            if ($('.logo-container').css("position") == "fixed") {
                //faceted nav
                if ($('.faceted-navbar .button-link').css("display") == "none") {
                    $('.faceted-navbar select').change(function () {
                        $(this).parents('form').trigger('submit');
                    });
                }
                
                //move country DD to faceted nav bar
                if ($('.faceted-navbar .navbar-nav.second #countries').length > 0) {
                    $('.faceted-navbar .navbar-nav.first').append($('.faceted-navbar .navbar-nav.second #countries'));
                    $('.faceted-navbar .navbar-nav.second').prepend($('.faceted-navbar .navbar-nav.first #levels'));
                }
                //display more than 2 filters in dropdown button nav on product list page
                if ($('body.product-list-page #slideContainer').length > 0) {

                    $('body.product-list-page aside[role="complementary"]').append('<div id="faceted-navbar-collapse"></div>');
                    $('.main-container aside[role="complementary"]').prepend('<div id="slideClose"><i class="fa fa-times"></i></div>');
                    $('#faceted-navbar-collapse').append($('.faceted-navbar .navbar-nav.second'));

                }
                $('#block-sab-faceted-nav-sab-faceted-nav-product-list .navbar-toggle').click(function () {
                    $('.main-container aside[role="complementary"]').slideDown("slow");
                });

                //submit faceted nav on general page when DD changed
                $('#get-sab-faceted-nav-general-form select').change(function (e) {
                    e.preventDefault();
                    $(this).parents('form').submit();
                });
            }

            //<=840px 
            if ($(this).width() <= 840 && $('#header-menu').css('font-size') >= '14px') {

                //show slideContainer only if aside exists and type is student guide, or blogs, or articles
                //if ($('.main-container aside[role="complementary"]').length > 0 && ($('body.node-type-student-guide #slideContainer').length > 0 || $('body.page-blogs #slideContainer').length > 0) || $('body.page-resources #slideContainer').length >0 || $('body.node-type-article-page').length >0) {
            if ($('.main-container aside[role="complementary"]').length > 0 && $('body:not(.product-list-page) #slideContainer').length > 0) {
                $('#slideContainer').addClass('show');
                $('.main-container aside[role="complementary"]').prepend('<div id="slideClose"><i class="fa fa-times"></i></div>');
            }

                //add Read More to content for program detail
            if ($(".program-details-holder").length > 0) {
                if ($(".program-details-holder .region-content-column-one #detail-read-more").length == 0) {
                    $('.program-details-holder .region-content-column-one').append('<a id="detail-read-more" href="#"><i class="fa fa-chevron-circle-down"></i></a>');
                    $('.program-details-holder .block-sab-program-details:not(#block-sab-program-details-sab-program-details-summary)').addClass('more-content');
            }

                var org_s = $("#block-sab-program-details-sab-program-details-summary .content").html().trim();

                if (org_s.split(' ').length > Drupal.settings.hide_content_by_words) {

                    var show_s = org_s.split(' ').slice(0, Drupal.settings.hide_content_by_words -1).join(' ');
                    var more_s = org_s.split(' ').slice(Drupal.settings.hide_content_by_words -1).join(' ');
                    $("#block-sab-program-details-sab-program-details-summary .content").html('<div class="more-content show">' +show_s + '</div><div class="more-content">' +more_s + '</div>');
            }
            }

                //add Read More to content for institution detail       
            if ($(".sab-school-details").length > 0) {

                if ($(".sab-school-details #detail-read-more").length == 0) {
                    $('.sab-school-details').append('<a id="detail-read-more" href="#"><i class="fa fa-chevron-circle-down"></i></a>');
            }

                var org_s = $(".sab-school-detail-description").html().trim();

                if (org_s.split(' ').length > Drupal.settings.hide_content_by_words) {

                    var show_s = org_s.split(' ').slice(0, Drupal.settings.hide_content_by_words -1).join(' ');
                    var more_s = org_s.split(' ').slice(Drupal.settings.hide_content_by_words -1).join(' ');
                    $(".sab-school-detail-description").html('<div class="more-content show">' +show_s + '</div><div class="more-content">' +more_s + '</div>');
            }
            }
            $("#detail-read-more").on('click', function (e) {

                e.preventDefault();

                $(this).toggleClass("expended");

                if ($(this).hasClass('expended')) {

                    $(".more-content, .more-content.show img").slideDown("slow", function () {
                        $('#detail-read-more i').removeClass("fa-chevron-circle-down").addClass("fa-chevron-circle-up");

                });
                } else {
                    $(".more-content:not(.show), .more-content.show img").slideUp("slow", function () {
                        $('#detail-read-more i').removeClass("fa-chevron-circle-up").addClass("fa-chevron-circle-down");

                });
            }
            });

                //product list: move oas-ads from aside to below content
            $('<div id="sab-oas-ads-mobile-container"></div>').insertAfter($('body.product-list-page .main-container .block-system'));
            $('#sab-oas-ads-mobile-container').append($('body.product-list-page aside .block-sab-oas-ads'));

                //product list: move related article and reviews from aside to below listing
            $('body.product-list-page .main-container .region-content').append($('<div id="sab-no-ads-mobile-container"></div>'));
            $('#sab-no-ads-mobile-container').append($('body.product-list-page aside .block:not(.block-sab-oas-ads)'));

    }
        }

        function rotateTestimonial(index) {
            
            $("#lp-testimonials #t" + index).css('display', 'inline-block');
            $("#lp-testimonials").css('height', $("#lp-testimonials #t" + index).css('height'));
            setTimeout(function () {
                $("#lp-testimonials #t" + index).slideUp();

                if ($("#lp-testimonials #t" + (index + 1)).length > 0) {
                    rotateTestimonial(index + 1);
                }else {               
                    rotateTestimonial(0);
                }
            }, 5000);
            
        }
    
});


})(jQuery);

