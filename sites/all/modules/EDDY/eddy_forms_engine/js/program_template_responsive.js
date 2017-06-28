(function ($) {

    $(document).ready(function () {

        if ($('#ResponsiveWidth').length == 0)
            $("body").append('<div id="ResponsiveWidth" class="hide"></div>');


        setTimeout(function () {

            responsive_change_sidebar()
        }, 300);


        $(".read-more a").live('click', function (e) {
            e.preventDefault();
            if ($(this).text() == "Read More") {
                $(this).parent().prev().find("ul li:not(:first-child):not(:nth-child(2))").slideDown();
                $(this).text("Read Less");
            } else {
                $(this).parent().prev().find("ul li:not(:first-child):not(:nth-child(2))").slideUp();
                $(this).text("Read More");
            }
        });

    });

    var width = $(window).width();

    var resize_continue = false;

    $(window).resize(function () {
        //only width change makes resize happen
        if ($(this).width() != width) {
            width = $(this).width();

            responsive_change_sidebar();

        }

    });

    function responsive_change_sidebar() {

        if ($("#ResponsiveWidth").length > 0) {

            var responsive_width = $("#ResponsiveWidth").css("width").replace("px", "");

            if (responsive_width <= 768) {

                //$(".form #column-narrow").hide();
                $(".thankyou .ad-holder").after($(".thankyou #UserSelections"));

                if ($("#responsive-school-info").length == 0 && $('#columns-wrapper.form').length > 0) {

                    $("#columns-wrapper").before('<div id="responsive-school-info"><div class="logo-holder">' + $(".school-logo").html() + '</div><div class="school-info-holder"><h2>' + $("#school-name").text() + '</h2><h3>' + $("#program-name").html() + '</h3></div></div>');
                    $("#columns-wrapper").before('<div id="responsive-toggle-details-holder"><a class="responsive-view-program-info" href="#">See Program Info</a><a class="responsive-view-form active" href="#">Your Info</a></div>');

                }

                $(".responsive-view-program-info").click(function (e) {

                    e.preventDefault();
                    $("#column-wide").hide();
                    $("#column-narrow").fadeIn(100).css('display', 'block');

                    $(".responsive-view-form").text("Request Info");

                    $(this).addClass("active");

                });

                $(".responsive-view-form").click(function (e) {

                    e.preventDefault();
                    $("#column-wide").fadeIn(100);
                    $("#column-narrow").hide();

                    $(this).addClass("active").text("Your Info");

                });


            } else {
                $(".thankyou .udemy-ad").after($(".thankyou .ad-holder"));

                $("#responsive_slider_init").remove();

                $("#responsive-toggle-details-holder").remove();
                $("#responsive-school-info").remove();

                $("#column-wide").show();
                $("#column-narrow").show();
                if ($('#eddycrosssell').length == 0) {
                    $("#column-narrow").show();
                }

            }

            //When the site is less than or equal to 360px. 
            if (responsive_width <= 360) {

                $("#responsive-school-info .logo-holder img").css("width", "150px").css("height", "50px");

            } else {

                $("#responsive-school-info .logo-holder img").css("width", "240px").css("height", "80px");

            }


        }

        $("#responsive-toggle-details-holder a").click(function (e) {

            e.preventDefault();
            $("#responsive-toggle-details-holder a").removeClass("active");
            $(this).addClass("active");

        });

    }

})(jQuery);