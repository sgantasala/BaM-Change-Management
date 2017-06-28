(function ($) {

    $(document).ready(function () {
        
        $('.block-sab-landing-page form select').change(function () {

            var qs = $(this).parents("form").find('select:has(option[value!=""]:selected)').serialize();
            var action = $(this).parents('form').attr("action");
            var url = action.split("?")[0];            
            
            window.location.href = url + "?" + qs;
        });

        currentQS = location.href.split('?')[1];
        qsstring = '';
        if (currentQS != "" && currentQS != undefined && currentQS != 'undefined') {
            qsstring = '?'+ currentQS;
        }
        $(".landing_page_program_list_container").each(function (i) {
            $.ajax({
                url: '/landing-page-ajax/' + qsstring,
                context: this,
                success: function (data) {

                    $(this).html(data);
                }
            });
        });
    });


})(jQuery);

