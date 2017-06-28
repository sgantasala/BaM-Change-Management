(function ($) {

    function setFullDegreeSelectLabels() {

        $('#faceted_nav_home_student_levels_levels_id').find('option[value="6771"]').text('Undergrad student');
        $('#faceted_nav_home_student_levels_levels_id').find('option[value="700"]').text('Grad Student');
        $('#faceted_nav_home_student_levels_levels_id').find('option[value="696"]').text('Highschool student');
        $('#faceted_nav_home_student_levels_levels_id').find('option[value="6768"]').text('Gap Year student');

        $('#faceted_nav_home_student_levels_levels_id').find('option[value="6766"]').text('Undergraduate');
        $('#faceted_nav_home_student_levels_levels_id').find('option[value="6767"]').text('Graduate');
        $('#faceted_nav_home_student_levels_levels_id').find('option[value="6769"]').text('High School');


    }
    function setDefaultSelectLabels() {

        $('#faceted_nav_home_student_levels_levels_id').find('option[value="6766"]').text('Undergrad student');
        $('#faceted_nav_home_student_levels_levels_id').find('option[value="6767"]').text('Grad Student');
        $('#faceted_nav_home_student_levels_levels_id').find('option[value="6769"]').text('Highschool student');
        $('#faceted_nav_home_student_levels_levels_id').find('option[value="6768"]').text('Gap Year student');

        $('#faceted_nav_home_student_levels_levels_id').find('option[value="6771"]').text('Master');
        $('#faceted_nav_home_student_levels_levels_id').find('option[value="700"]').text('Doctorate');
        $('#faceted_nav_home_student_levels_levels_id').find('option[value="696"]').text('Bachelor');


    }

    $(document).ready(function () {

        //Faceted Nav for Product List Section
        if (Drupal != undefined && Drupal != 'undefined' && Drupal.hasOwnProperty('settings') && Drupal.settings.hasOwnProperty('basePath') && Drupal.settings.hasOwnProperty('plid')) {

            $(".faceted-navbar-container").html("Loading...");

            qs = "";

            if (location.href.split('?').length > 1) {

                qs += "?" + location.href.split('?')[1];

            }

            if (Drupal.settings.hasOwnProperty('nid')) {

                if (qs == "") {

                    qs += '?nid=' + Drupal.settings.nid;

                } else {

                    qs += '&nid=' + Drupal.settings.nid;

                }

            }

            $.get(Drupal.settings.basePath + "ajax/sab-faceted-nav/" + Drupal.settings.plid + qs, function (data) {

                $(".faceted-navbar-container").html(data);
                
                $('.dropdown-toggle').dropdown();

                //fix 81539
                $('.faceted-navbar-container ul.nav li.dropdown').hover(function () {
                    $(this).find('.dropdown-menu').stop(true, true).delay(100).fadeIn();
                }, function () {
                    $(this).find('.dropdown-menu').stop(true, true).delay(100).fadeOut();
                });

                if ($('.logo-container').css("position") == "fixed") {

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

                }


            });

        }

        //faceted navigation
        $('.faceted-nav-select-wrap select, #sab-landing-page-filters select').each(function () {
            //by adding size restict to show scrollbar
            //$(this).attr("size", "5");
            $(this).parent().next().val($(this).find("option:selected").text());
            $(this).attr("title", $(this).find("option:selected").text());
            $(this).parent().next().css('width', $(this).width() + 'px');
        });
        $('.faceted-nav-select-wrap select, #sab-landing-page-filters select').on("change", function () {
            $(this).parent().next().val($(this).find("option:selected").text());
            $(this).attr("title", $(this).find("option:selected").text());
            //$(this).parent().css('opacity', '0');
        });

        //rebind event on drop down which options are drupal form api ajax driven
        Drupal.behaviors.mybehavior = {
            attach: function (context, settings) {

                $(context).find('.faceted-nav-select-wrap select').each(function () {
                    $(this).parent().next().val($(this).find("option:selected").text());
                    $(this).attr("title", $(this).find("option:selected").text());
                    $(this).parent().next().css('width', $(this).width() + 'px');
                });

                $(context).find('.faceted-nav-select-wrap select').change(function () {
                    $(this).parent().next().val($(this).find("option:selected").text());
                    $(this).attr("title", $(this).find("option:selected").text());
                });
            }
        };

    });

    $(document).on('change', '#faceted_nav_home_sab_program_types_program_types_id', function () {
        if ($('#faceted_nav_home_sab_program_types_program_types_id').val() == 6437) {
            // setFullDegreeSelectLabels();
        } else {
            // setDefaultSelectLabels();
        }
    });

    Drupal.homeAjax = {
        // faceted nav form
        form_id: 'get-sab-faceted-nav-home-form'
    };

    Drupal.behaviors.homeAjax = {
        attach: function (context, settings) {
            // We extend Drupal.ajax objects for all AJAX elements in our form 
            for (ajax_el in settings.ajax) {
                if (Drupal.ajax[ajax_el].element.form) {
                    if (Drupal.ajax[ajax_el].element.form.id === Drupal.homeAjax.form_id) {
                        Drupal.ajax[ajax_el].beforeSubmit = Drupal.homeAjax.beforeSubmit;
                        Drupal.ajax[ajax_el].success = Drupal.homeAjax.success;
                        Drupal.ajax[ajax_el].error = Drupal.homeAjax.error;
                    }
                }
            }
        }
    };

    // Disable button
    Drupal.homeAjax.beforeSubmit = function (form_values, form, options) {
        $(form[0].elements).not(':disabled')
                            .addClass('home-ajax-disabled')
                            .attr('disabled', true);
    }

    // Enable form
    Drupal.homeAjax.enableForm = function (form) {
        $(form).find('.home-ajax-disabled')
                .removeClass('home-ajax-disabled')
                .attr('disabled', false);

    }

    Drupal.homeAjax.success = function (response, status) {
        Drupal.homeAjax.enableForm(this.element.form);
        // Call original method with main functionality
        Drupal.ajax.prototype.success.call(this, response, status);
    }
    Drupal.homeAjax.error = function (response, uri) {
        Drupal.homeAjax.enableForm(this.element.form);
        // Call original method with main functionality
        Drupal.ajax.prototype.error.call(this, response, uri);
    }

}(jQuery));


