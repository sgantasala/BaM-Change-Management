
(function ($) {
    $(document).ready(function () {

        $('.operation').not('.edit').on('click', function (e) {
            
            e.preventDefault();
            var irow = $(this).parents('tr');
            
            $.ajax({
                url: $(this).attr("rel"),
                context: this,
                success: function (data, irow) {
                    
                    var irow = $(this).parents('tr');
                    
                    if (data != ''){
                        switch(data.toLowerCase()){
                            case "deleted":                                
                                location.reload();
                                break;
                            case "published":
                                $(irow).find('.views-field-status').text(data);
                                $(irow).find('.views-field-rid a:last').remove();
                                break;
                            case "approved":
                                $(irow).find('.views-field-status').text(data);
                                $(irow).find('.views-field-rid a:last').text("Publish");

                                //replace href with new operation url
                                href_o = $(irow).find('.views-field-rid a:last').attr("rel");
                                op = href_o.split("/");
                                op[op.length - 1] = "publish";                                
                                $(irow).find('.views-field-rid a:last').attr("rel", op.join("/"));
                                break;
                            default:
                                $(irow).find('.views-field-status').text(data);
                                break;

                        }
                        
                    }    


                }
            });
        });

        


        /** reviews on detail **/
        //hide load more if reviews less than 5
        if ($('#review-detail-widget ul').length == 1) {
            $('#review-detail-widget .reviews-load-more').hide();
        }
        $('#review-detail-widget .reviews-load-more').on("click", function (e) {
            e.preventDefault();
            $(this).parent('ul').find('.reviews-load-more').hide();
            $(this).parent('ul').next('ul').show();
            if ($(this).parent('ul').next('ul').next('ul').length = 0) {
                $(this).parent('ul').next('ul').next('ul').find('.reviews-load-more').hide();
            }
        });
        $('.review-read-more').click(function (e) {
            e.preventDefault();
            if ($(this).text() == 'read more') {
                $(this).prev('.collapsed').css('display', 'inline');
                $(this).text('read less');
            } else {
                $(this).prev('.collapsed').css('display', '');
                $(this).text('read more');
            }
        });
        /** reviews on admin **/
       
        var rating = $('#eddy_reviews_container .review-rating .form-type-radios input[type="radio"]:checked').attr("value");
        set_rating(rating);
        //$('#eddy_reviews_container .review-rating .form-type-radios input[type="radio"]').attr('checked', true).trigger('click');

        $('#eddy_reviews_container .review-rating .form-type-radios input[type="radio"]').on('click', function () {
            var rating = $(this).attr("value");
            set_rating(rating);
        });

    });
    //end of document ready

    function set_rating(rating){
        $('#eddy_reviews_container .review-rating .form-type-radios input[type="radio"]').each(function () {
            $(this).parent().removeClass("rated");
            if ($(this).attr("value") <= rating) {
                $(this).parent().addClass("rated");
            }
        });
    }
})(jQuery);
