(function ($) {

    function hide_form_from_left_side() {

        if ($("#demo-inner-html .eddy-form-container").length > 0) {

            // $(".sidebar-nav .eddy-form-container").parents('.box').hide();

        } else {

            // $(".sidebar-nav .eddy-form-container").parents('.box').show();

        }

        if ($("#demo-inner-html #nomatch-ads-container").length > 0) {

            $(".sidebar-nav #nomatch-ads-container").parents('.box').hide();

        } else {

            $(".sidebar-nav #nomatch-ads-container").parents('.box').show();

        }

        var warn_items = [{
            id: 1,
            elem: "#demo-inner-html .workflow-container.thankyou-container",
            warn_msg: "Form Defaults - Thank You field is not added to the page"
        },
                          {
                              id: 2,
                              elem: "#demo-inner-html .workflow-container.nothankyou-container",
                              warn_msg: "Form Defaults - No Thank You field is not added to the page"
                          }];

        var warn_message = '';

        $.each(warn_items, function () {

            if ($(this.elem).length <= 0) {
                warn_message += "<li>" + this.warn_msg + "</li>";
            }
        });

        $('.warning-message-container').html(warn_message);

        if ($('.warning-message-container').html() === "") {

            $('.warning-message-container').hide();
        } else {

            $('.warning-message-container').show();
        }
    }

    function handleJsIds() {
        handleModalIds(), handleAccordionIds(), handleCarouselIds(), handleTabsIds()
    }

    function handleAccordionIds() {
        var t, e = $("#demo-inner-html #myAccordion"),
            i = randomNumber(),
            n = "panel-" + i;
        e.attr("id", n), e.find(".panel").each(function (e, i) {
            t = "panel-element-" + randomNumber(), $(i).find(".panel-title").each(function (e, i) {
                $(i).attr("data-parent", "#" + n), $(i).attr("href", "#" + t)
            }), $(i).find(".panel-collapse").each(function (e, i) {
                $(i).attr("id", t)
            })
        })
    }

    function handleCarouselIds() {
        var t = $("#demo-inner-html #myCarousel"),
            e = randomNumber(),
            i = "carousel-" + e;
        t.attr("id", i), t.find(".carousel-indicators li").each(function (t, e) {
            $(e).attr("data-target", "#" + i)
        }), t.find(".left").attr("href", "#" + i), t.find(".right").attr("href", "#" + i)
    }

    function handleModalIds() {
        var t = $("#demo-inner-html #myModalLink"),
            e = randomNumber(),
            i = "modal-container-" + e,
            n = "modal-" + e;
        t.attr("id", n), t.attr("href", "#" + i), t.next().attr("id", i)
    }

    function handleTabsIds() {
        var t = $("#demo-inner-html #myTabs"),
            e = randomNumber(),
            i = "tabs-" + e;
        t.attr("id", i), t.find(".tab-pane").each(function (t, e) {
            var i = $(e).attr("id"),
                n = "panel-" + randomNumber();
            $(e).attr("id", n), $(e).parent().parent().find("a[href=#" + i + "]").attr("href", "#" + n)
        })
    }

    function randomNumber() {
        return randomFromInterval(1, 1e6)
    }

    function randomFromInterval(t, e) {
        return Math.floor(Math.random() * (e - t + 1) + t)
    }

    function gridSystemGenerator() {
        $(".lyrow .preview input").bind("keyup", function () {
            var t = 0,
                e = "",
                i = !1,
                n = $(this).val().split(" ", 12);
            $.each(n, function (n, s) {
                i || (parseInt(s) <= 0 && (i = !0), t += parseInt(s), e += '<div class="col-md-' + s + ' column"></div>')
            }), 12 != t || i ? $(this).parent().prev().hide() : ($(this).parent().next().children().html(e), $(this).parent().prev().show())
        })
    }

    function stepElm() {

        $(".step-container input").bind("keyup", function () {

            if (isNaN($(this).val())) {

                $(this).val("");
                $(this).parents(".step-container").find(".ui-draggable-handle").addClass('display-none');

            } else {

                $(this).parents(".step-container").find(".view div").attr('class', 'show-step-' + $(this).val());
                $(this).parents(".step-container").find(".view h2 span").text($(this).val());
                $(this).parents(".step-container").find(".ui-draggable-handle").removeClass('display-none');

            }

        });

    }

    function configurationElm(t, e) {
        $("#demo-inner-html").on("click", ".configuration > a", function (t) {
            t.preventDefault();
            var e = $(this).parent().next().next().children();
            $(this).toggleClass("active"), e.toggleClass($(this).attr("rel"))
        }), $("#demo-inner-html").on("click", ".configuration .dropdown-menu a", function (t) {
            t.preventDefault();
            var e = $(this).parent().parent(),
                i = e.parent().parent().next().next().children();
            e.find("li").removeClass("active"), $(this).parent().addClass("active");
            var n = "";
            e.find("a").each(function () {
                n += $(this).attr("rel") + " "
            }), e.parent().removeClass("open"), i.removeClass(n), i.addClass($(this).attr("rel"))
        });

    }

    function removeElm() {
        $("#demo-inner-html").on("click", ".remove", function (t) {
            t.preventDefault(), $(this).parent().remove(), !$("#demo-inner-html .lyrow").length > 0 && clearDemo();

            hide_form_from_left_side();
        })
    }

    function editElm() {




        $(".edit-widget").click(function (e) {

            e.preventDefault();

            $(this).parents(".box").addClass('current-editor-modal');

            $('#editorModal textarea').val($(this).parents(".box").find('.view').html());

            if (CKEDITOR) {
                CKEDITOR.instances['edit-edit-modal-value'].setData($(this).parents(".box").find('.view').html());
            }

            $('#editorModal').modal('show');

        });





        $("#eddy-drag-drop-modal-save").click(function (e) {

            var data = $('#editorModal textarea').val();

            if (CKEDITOR) {
                data = CKEDITOR.instances['edit-edit-modal-value'].getData();
            }

            $('.current-editor-modal').find('.view').html(data);
            $('.current-editor-modal').removeClass('current-editor-modal');
            $('#editorModal').modal('hide');

        });

        $("#eddy-drag-drop-modal-cancel, #editorModal .close").click(function (e) {

            $('.current-editor-modal').removeClass('current-editor-modal');
            $('#editorModal').modal('hide');

        });
        $('*[contenteditable]').click(function (e) {
            $(this).attr('contenteditable', true);
        });

    }

    function clearDemo() {
        $("#demo-inner-html").empty()
    }

    function removeMenuClasses() {
        $("#menu-layoutit li button").removeClass("active")
    }

    function changeStructure(t, e) {
        $("#download-layout ." + t).removeClass(t).addClass(e)
    }

    function cleanHtml(t) {
        $(t).parent().append($(t).children().html())
    }

    function cleanLayoutSrc() {

        var t = $("#demo-inner-html").clone(true);

        t.find(".preview, .configuration, .drag, .remove, .edit-widget").remove(), t.find(".lyrow").addClass("removeClean"), t.find(".box-element").addClass("removeClean"), t.find(".lyrow .lyrow .lyrow .lyrow .lyrow .removeClean").each(function () {
            cleanHtml(this)
        }), t.find(".lyrow .lyrow .lyrow .lyrow .removeClean").each(function () {
            cleanHtml(this)
        }), t.find(".lyrow .lyrow .lyrow .removeClean").each(function () {
            cleanHtml(this)
        }), t.find(".lyrow .lyrow .removeClean").each(function () {
            cleanHtml(this)
        }), t.find(".lyrow .removeClean").each(function () {
            cleanHtml(this)
        }), t.find(".removeClean").each(function () {
            cleanHtml(this)
        });

        t.find(".removeClean").remove();
        t.find(".column").removeClass("ui-sortable").removeClass("column");

        var output = $.htmlClean(t.html(), {
            //Hack Provided by html clean to not exclude Iframe tags
            removeTags: ["basefont"],
            format: !0,
            allowedAttributes: [
                ["id"],
                ["class"],
                ["name"],
                ["data-toggle"],
                ["data-target"],
                ["data-parent"],
                ["role"],
                ["data-dismiss"],
                ["aria-labelledby"],
                ["aria-hidden"],
                ["data-slide-to"],
                ["data-slide"],
                ["data-interval"],
                ["src"]
            ]
        });



        return output;

    }

    $(window).resize(function () {
        $("body").css("min-height", $(window).height() - 90), $("#demo-inner-html").css("min-height", $(window).height() - 160)
    }),

	$(document).ready(function () {
	    if (CKEDITOR) {
	        CKEDITOR.config.allowedContent = true;
	        CKEDITOR.config.enterMode = CKEDITOR.ENTER_BR;
	        CKEDITOR.config.autoParagraph = false;
	        CKEDITOR.config.protectedSource.push(/<i[^>]*><\/i>/g);
	        CKEDITOR.config.extraAllowedContent = '*{*}';
	    }
	    if ($(".header-container").length > 0) {
	        $('html, body').animate({
	            scrollTop: $(".header-container").offset().top - 100
	        }, 2000);
	    }
	    hide_form_from_left_side();

	    $("body").css("min-height", $(window).height() - 90), $("#demo-inner-html").css("min-height", $(window).height() - 160), $("#demo-inner-html, #demo-inner-html .column").sortable({
	        connectWith: ".column",
	        opacity: .35,
	        handle: ".drag"
	    }), $(".sidebar-nav .lyrow").draggable({
	        connectToSortable: "#demo-inner-html",
	        helper: "clone",
	        handle: ".drag",
	        drag: function (t, e) {
	            e.helper.width(400)
	        },
	        stop: function (t, e) {
	            $("#demo-inner-html .column").sortable({
	                opacity: .35,
	                connectWith: ".column"
	            });
	        }
	    }), $(".sidebar-nav .box").draggable({
	        connectToSortable: ".column",
	        helper: "clone",
	        handle: ".drag",
	        drag: function (t, e) {
	            e.helper.width(400)
	        },
	        stop: function (t, e) {
	            handleJsIds();
	            if (CKEDITOR) {
	                $('*[contenteditable]', $(this)).each(function (i, editableElement) {
	                    $(this).attr('contenteditable', true);
	                });
	            }
	            hide_form_from_left_side();
	            editElm();
	        }
	    });

	    $(document).on("hidden.bs.modal", function (t) {
	        $(t.target).removeData("bs.modal")
	    });

	    $(".nav-header").click(function () {
	        $(".sidebar-nav .boxes, .sidebar-nav .rows").hide(), $(this).next().slideDown()
	    }), removeElm(), editElm(), configurationElm(), gridSystemGenerator(), stepElm();

	    $(".clear-button-holder button").click(function (e) {
	        e.preventDefault();
	        clearDemo();
	    });

	    $(".actions-holder .save-button-holder .form-submit").click(function (e) {

	        $(this).unbind('click');

	        $("#demo-inner-html").find(".eddy-form-container").html("");

	        var form_html = $("#demo-inner-html").html();

	        $("#eddy-seo-drag-drop-raw-form textarea").val(form_html);

	        $("#eddy-seo-drag-drop-clean-form textarea").val(cleanLayoutSrc(form_html));

	        $(this).bind('click');

	    });

	});


})(jQuery);