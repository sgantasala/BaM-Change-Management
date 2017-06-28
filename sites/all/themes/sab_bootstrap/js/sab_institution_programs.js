

(function ($) {

    $(document).ready(function () {

        //if ($('#ResponsiveWidth').length == 0)
        //    $("body").append('<div id="ResponsiveWidth" class="hide"></div>');

        //setTimeout(function () {

        //     responsive_change_sidebar()
        //}, 300);
         
    });


    //var width = $(window).width();

    //var resize_continue = false;

    //$(window).resize(function () {
    //    //only width change makes resize happen
    //    if ($(this).width() != width) {
    //        width = $(this).width();

    //        responsive_change_sidebar();
           
    //    }
       
    //});


    //function responsive_change_sidebar() {
       
    //    if ($("#ResponsiveWidth").length > 0) {

    //        var responsive_width = $("#ResponsiveWidth").css("width").replace("px", "");

           
    //        if (responsive_width <= 768) {



    //            jQuery(".sab-school-program-details .sab-school-program-rating").each(function () {

    //                if (jQuery(this).parent('.sab-school-program-detail-left')) {
                   
    //                    jQuery(this).parent().prev().append(jQuery(this));
                      
    //                }
    //            });

    //            //if(jQuery("#sab-school-program-items-id").hasClass("container")) {

    //            //    jQuery("#sab-school-program-items-id").removeClass("container");
    //            //} 
    //            //else {
    //            //    jQuery("#sab-school-program-items-id").addClass("container");
    //            //} 
    //            jQuery(".sab-school-program-details").each(function () {
    //                if (jQuery(this).find("#sab-school-program-detail-left-id").hasClass("col-xs-10")) {

    //                    jQuery(this).find("#sab-school-program-detail-left-id").removeClass("col-xs-10");
    //                    jQuery(this).find("#sab-school-program-detail-left-id").addClass("col-xs-8");

    //                }
    //                else {
    //                    jQuery(this).find("#sab-school-program-detail-left-id").removeClass("col-xs-8");
    //                    jQuery(this).find("#sab-school-program-detail-left-id").addClass("col-xs-10");
    //                }
               
    //                if (jQuery(this).find("#sab-school-program-detail-button-holder-id").hasClass("col-xs-2")) {

    //                    jQuery(this).find("#sab-school-program-detail-button-holder-id").removeClass("col-xs-2");
    //                    jQuery(this).find("#sab-school-program-detail-button-holder-id").addClass("col-xs-4");

    //                }
    //                else {
    //                    jQuery(this).find("#sab-school-program-detail-button-holder-id").removeClass("col-xs-4");
    //                    jQuery(this).find("#sab-school-program-detail-button-holder-id").addClass("col-xs-2");
    //                }
    //            });
 
                


    //        }  


    //        SetProgramItemHeight(responsive_width);
            
    //    }

         

    //}
             

    //function SetProgramItemHeight(responsive_width) {
         
    //    var tall = 0;

    //    $('.sab-program-item-holder').each(function (index, item) {
    //        tall = 0;

    //        $(item).find("li").each(function (i, j) {

    //            if ($(j).hasClass('sab-school-program-item')) {

    //                if ($(j).outerHeight() > tall) {

    //                    tall = $(j).outerHeight();
    //                }
    //            }
    //        });

    //         if (responsive_width >= 992) {
    //            $(item).find("li").each(function (i, l) {
    //                 $(l).css("min-height", "");

    //                if ($(l).hasClass('sab-school-program-item')) {
                     
    //                    $(l).css('min-height', tall );
    //                }
                    
                  
    //            });
    //        } else {

    //            $(item).find("li").each(function (k, m) {
    //                $(m).css("min-height", "");

    //                if ($(m).hasClass('sab-school-program-item')) {

    //                    tall = $(m).outerHeight();
    //                    $(m).css('min-height', tall );
    //                }
 
    //            });

    //        }

    //    });
    //}
})(jQuery);

