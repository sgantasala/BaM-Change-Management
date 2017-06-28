(function ($) {

    $(document).ready(function () {

        if ($("#wizard-school-info-holder").length == 0 && $('#columns-wrapper.form').length > 0) {

            $("#eddy-form-container").before('<div id="wizard-school-info-holder"><h2 class="wizard-school-name">' + $('.school-logo img').attr('alt') + '</h2><h3 class="wizard-program-name program-name"></h3></div>');

        }

        if ($('.school-logo').length > 0 && $('.school-logo').css('display') == 'inline-block') {
            $('.school-logo img').addClass("img-responsive");
            $('#wizard-school-info-holder').before($('.school-logo'));
        }

    });

    $(FormsEngine).on("WorkflowChanged", function (event, data) {

        switch (data) {
            case 'THANKYOU':
                $("#wizard-school-info-holder").css("display", "none");
                $("#column-narrow").css("display", "none");
                $("#column-wide").css("width", "100%");
                break;
        }

    });

})(jQuery);