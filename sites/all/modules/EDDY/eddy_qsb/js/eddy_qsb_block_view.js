
var level, category, subject, subject_id;
var ServiceCall = 1;

var trailing_slash = "";

var first_dropdown_mapping = {};
first_dropdown_mapping['Category'] = {};
first_dropdown_mapping['EduLevel'] = {};
first_dropdown_mapping['Category'][0] = {};
first_dropdown_mapping['Category'][1] = {};
first_dropdown_mapping['EduLevel'][1] = {};


var second_dropdown_mapping = {};
second_dropdown_mapping['Category'] = {};
second_dropdown_mapping['EduLevel'] = {};
second_dropdown_mapping['Category'][0] = {};
second_dropdown_mapping['Category'][1] = {};
second_dropdown_mapping['EduLevel'][1] = {};


var third_dropdown_mapping = {};
third_dropdown_mapping['Category'] = {};
third_dropdown_mapping['EduLevel'] = {};
third_dropdown_mapping['Category'][0] = {};
third_dropdown_mapping['Category'][1] = {};
third_dropdown_mapping['EduLevel'][1] = {};

//var webservice_hook_menu = "/service/loadqsb/";
(function ($) {

    var subject_mapping = new Array();

    var webservice = {};
    webservice['Category'] = {};
    webservice['EduLevel'] = {};

    webservice['Category'][0] = "/service/loadqsb_2"; // 2 dropdown, category is the first
    webservice['EduLevel'][1] = "/service/loadqsb"; // 3 dropdown, level is the first
    webservice['Category'][1] = "/service/loadqsb_c"; // 3 dropdown, category is the first


    $(document).ready(function () {

        //if (Drupal.settings.prechk_filter) {
        //    depend['Category'][1] = [[true, true], [false, false, false]]; //3 dropdown, edulevel is the first
        //    depend['EduLevel'][0] = [[false, false], ['', '', '']]; //3 dropdown, edulevel is the first
        //    depend['EduLevel'][1] = [[false, false], [true, false, true]]; //3 dropdown, edulevel is the first            
        //}
        if (Drupal.settings.trailing_slash)
            trailing_slash = '/';


        //inactive select with inactive class name
        $('.qdf-holder select.inactive').attr("disabled", "disabled");
        $('.qdf-holder select.hide').parent().hide();

        var cidGuid = $(".cid").val();
        var qsbType = $(".qsb_type");
        var qsbForm = $('.block-eddy-qsb');

        // Load QSB Questions Data
        // search each QSB's QSB type	
        // maybe more than 1 QSB on the page	



        // Degree QSB
        // call web service to load Level, Category, and Subject when degreeStatic.degree_text = "Degree", which is set in qsb module file
        $(qsbForm).each(function () {

            // 
            var target_type = $(this).find('form').attr("target-type");
            var question_level = $(this).find('li.qsb-question').length - 2;
            var first_qq = $(this).find('form li.qsb-question:first').attr("class").split(' ')[0];
            var second_qq = $(this).find('form li.qsb-question:nth-child(2)').attr("class").split(' ')[0];
            var third_qq = '';
            if (question_level == 1)
                third_qq = $(this).find('form li.qsb-question:nth-child(3)').attr("class").split(' ')[0];



            // automatic load first dropdown	            
            get_first_dropdown_data($(this).find('li.' + first_qq), webservice[first_qq][question_level], target_type, question_level);

            if (second_qq != '' && depend[first_qq][question_level][0][0] == false) {

                get_second_dropdown_data($(this).find('li.' + second_qq), webservice[first_qq][question_level] + "/0", target_type, question_level);
            }

            // if(depend[1] == false){              
            if (third_qq != '' && depend[first_qq][question_level][1][0] == false) {

                get_third_dropdown_data($(this).find('li.' + third_qq), webservice[first_qq][question_level] + "/0/0", target_type, question_level);
            }


            //select degree level event
            $(this).find('li.' + first_qq + ' select').live("change", function () {

                if ($(this).val() != "-1") {


                    if (second_qq != '' && depend[first_qq][question_level][0][1] == true) {

                        qsb_question_unselect($(this));

                        var service = webservice[first_qq][question_level] + "/" + first_dropdown_mapping[first_qq][question_level][$(this).val()][0];

                        var item = $(this).parents('.qq-detail').find('li.' + second_qq);

                        qsb_question_loading(item);
                        if (item.length > 0) {

                            get_second_dropdown_data(item, service, target_type, question_level, $(this));

                        }
                    }

                    if (third_qq != '' && depend[first_qq][question_level][1][1] == true) {

                        qsb_question_unselect($(this));

                        var service = webservice[first_qq][question_level] + "/" + first_dropdown_mapping[first_qq][question_level][$(this).val()][0] + "/0";
                        var item = $(this).parents('.qq-detail').find('li.' + third_qq);
                        qsb_question_loading(item);

                        if (item.length > 0) {
                            get_third_dropdown_data(item, service, target_type, question_level, $(this));
                        }
                    }

                } else {
                    if (third_qq != '' && depend[first_qq][question_level][1][0] == false) {

                        var item = $(this).parents('.qq-detail').find('li.' + third_qq);
                        qsb_question_loading(item);

                        var service = webservice[first_qq][question_level] + "/0/0";
                        get_third_dropdown_data(item, service, target_type, question_level);

                    }
                    qsb_question_unselect($(this));
                }

            });

            // // select category event
            $(this).find('li.' + second_qq + ' select').live("change", function () {
                if ($(this).val() != "-1") {

                    if (third_qq != '' && depend[first_qq][question_level][1][2] == true) {



                        var field_1_Select = $(this).parents(".qq-detail").find(".qdf-" + first_qq + "-select");

                        qsb_question_unselect($(this));

                        var service = webservice[first_qq][question_level] + "/" + first_dropdown_mapping[first_qq][question_level][$(field_1_Select).val()][0] + "/" + second_dropdown_mapping[first_qq][question_level][$(this).val()][0];
                        var item = $(this).parents('.qq-detail').find('li.' + third_qq);

                        qsb_question_loading(item);

                        if (item.length > 0) {

                            get_third_dropdown_data(item, service, target_type, question_level, $(this));
                        }

                    }
                } else {
                    if (third_qq != '' && depend[first_qq][question_level][1][1] == true) {


                        var service = webservice[first_qq][question_level] + "/0/0";
                        var item = $(this).parents('.qq-detail').find('li.' + third_qq);

                        qsb_question_loading(item);

                        get_third_dropdown_data(item, service, target_type, question_level, $(field_1_Select));
                    }
                    qsb_question_unselect($(this));
                }
            });


            // Degree Finder Submit			
            $(this).find('form').live("submit", function (e) {

                var submit_type = $(this).find(".submit_type").val();
                var qType = $(this).find(".qsb_type").val();

                // degreeStatic.degree_text = "Degree", which is set in qsb module file
                // only check form validation when it's a Degree finder
                if (qType == Drupal.settings.degree_text) {

                    if (form_validate($(this), submit_type)) {

                        var url = generateURL($(this), question_level);

                        if (url == "") {
                            return false;
                        } else {
                            window.location = url;
                            return false;
                        }
                    } else {
                        return false;
                    }
                } else {
                    // Other situation, such as Campus Search, Career Search
                }
            });

        });

    });
    // end of document.ready



    function form_validate(formObj, submit_type) {
        //will check validation if this is a Degree qsb and submit to school form page

        var questions = formObj.find(".qdf-block-form-item");
        var count = 0;

        for (var i = 0; i < questions.length; i++) {
            var dropdown_class = $(questions[i]).prev('label').attr("for");
            var message = dropdown_class.split('-');
            message = message[message.length - 1];
            if (message == "EduLevel")
                message = "Level";
            if ($(questions[i]).val() == "-1" || $(questions[i]).val() == "loading") {
                alert("Please choose " + message);
                return false;
            }
        }

        return true;
    }



    function generateURL(formObj, question_level) {

        var first_qq = $(formObj).find('li.qsb-question:first').attr("class").split(' ')[0];
        var second_qq = $(formObj).find('li.qsb-question:nth-child(2)').attr("class").split(' ')[0];
        var third_qq = '';
        if (question_level == 1)
            third_qq = $(formObj).find('li.qsb-question:nth-child(3)').attr("class").split(' ')[0];


        //var appName = Drupal.settings.app_settings.appName;
        var submit_type = formObj.find(".submit_type").val();

        var actionUrl = ((submit_type == 'qdf-listing') ? "" : Drupal.settings.form_url);
        //var formUrl = "/regpath/elrn/track.aspx";
        var url_spec = formObj.find('.form_url').val();

        //Add Tracking
        //var trackingString = "";
        var url = "";

        //cid as trackingstring is no needed anymore
        //formObj.find(".tracking-param").each(function () {
        //	if (trackingString.length > 1) trackingString += '&';
        //	else trackingString = '?';
        //	trackingString += (this.name + "=" + this.value);
        //});

        if (submit_type == "qdf-form") {

            if (url_spec.substr(url_spec.length - 1) != '/')
                url_spec += trailing_slash;

            url = url_spec + get_query_string(formObj, question_level, first_qq);

        } else {
            //go listing url
            if (url_spec != "") {
                url = url_spec + get_query_string_for_listing(formObj, question_level, first_qq);
            } else {
                var first_field = '', second_field = '', third_field = '';
                if (formObj.find('li.' + first_qq + ' select').length > 0) {
                    first_field = formObj.find('li.' + first_qq + ' select').val();
                }

                if (formObj.find('li.' + second_qq + ' select').length > 0) {
                    second_field = formObj.find('li.' + second_qq + ' select').val();
                }
                if (third_qq != '' && formObj.find('li.' + third_qq + ' select').length > 0) {
                    third_field = formObj.find('li.' + third_qq + ' select').val();
                }

                url = "/" + get_listing_url(first_field, second_field, third_field, question_level, first_qq);
            }

            if (url.substr(url.length - 1) != '/')
                url += trailing_slash;


        }

        return url;
    }



    // call this function when user select any value from dropdown list except -1
    function qsb_question_select(eventObj) {
        if (eventObj.val() != "-1") {
            var qq_obj = eventObj.parent();
            if ((qq_obj.next() != null) && qq_obj.next().hasClass('qsb-question')) {
                //$(qq_obj).next().find('select').prepend('<option value="loading">' + loading_text + '</option>');
                //$(qq_obj).next().find('select option[value="loading"]').select();
                //qq_obj.next().find('select').
                if ($(qq_obj).next().find('select').hasClass('hide')) {
                    //$(currentDegreeSelect).parents(".qq-detail").find(".qdf-" + field_2_name + "-select").slideDown(300).parent().slideDown(300);
                    $(qq_obj).next().find('select').attr("disabled", "").show().parent().show();
                }
                if ($(qq_obj).next().find('select').hasClass('inactive')) {
                    $(qq_obj).next().find('select').attr("disabled", "").removeClass('inactive').addClass("active");
                }
            }
        }
    }


    // call this function when user select 'please select XXXXX' which value is -1 from dropdown list
    function qsb_question_unselect(eventObj) {


        var qq_obj = eventObj.parent();
        var i = 0;
        while (($(qq_obj).next() != null) && $(qq_obj).next().hasClass('qsb-question')) {

            //if(depend[i][1] == true){		
            //$(qq_obj).next().find('select').attr('disabled', 'disabled');
            $(qq_obj).next().find('select option[value!="-1"]').remove();

            $(qq_obj).next().find('select').val('-1');
            if (qq_obj.next().find('select').hasClass('hide')) {
                qq_obj.next().hide();
            }
            if (qq_obj.next().find('select').hasClass('active')) {
                qq_obj.next().find('select').removeClass('active').addClass('inactive').attr("disabled", "disabled");
            }
            //}
            qq_obj = $(qq_obj).next();
            i++;
        }

    }

    function qsb_question_loading(obj) {
        var loading_text = "Loading...";

        $(obj).find('select').prepend('<option value="loading">' + loading_text + '</option>');
        $(obj).find('select').val('loading');
        $(obj).find('select').attr('disabled', 'disabled');

    }

    function qsb_question_finish_loading(obj) {
        if ($(obj).find("select option:first").val() == 'loading') {
            $(obj).find("select option:first").remove();
        }
        $(obj).find("select").removeAttr("disabled");
    }

    function get_first_dropdown_data(first_item, service, target_type, question_level) {

        qsb_question_loading(first_item);

        service = service + trailing_slash + "?type=" + target_type;
        service = $.eddy_core.cache_buster.append_cache_buster_qs(service);

        var first_qq = $(first_item).attr("class").split(' ')[0];

        $.get(service, function (data) {
            var jsonObj = data.ask_items;

            if (jsonObj.length > 0) {
                for (var i = 0; i < jsonObj.length; i++) {

                    var ask_display = jsonObj[i]['showtitle'];
                    var ask_val = jsonObj[i]['showvalue'];
                    var ask_r_val = jsonObj[i]['realvalue'];
                    var alias_url = jsonObj[i]['listing_url'];

                    //subject_mapping[s_val] = alias_url;	
                    //first_dropdown_map(ask_val, ask_r_val, alias_url);

                    first_dropdown_map(ask_val, ask_r_val, alias_url, question_level, first_qq);
                    $(first_item).find('select').append('<option value="' + get_val_1(ask_val, ask_r_val, question_level) + '" isid="' + ask_r_val + '">' + ask_display + '</option>');
                }

                qsb_question_finish_loading(first_item);

                precheck(first_qq);
            }


        });


    }

    function get_second_dropdown_data(second_item, service, target_type, question_level, lasteventObj) {

        service = service + trailing_slash + "?type=" + target_type;
        service = $.eddy_core.cache_buster.append_cache_buster_qs(service);

        var first_qq = $(second_item).parent().find('li.qsb-question:first').attr("class").split(' ')[0];
        var second_qq = $(second_item).attr("class").split(' ')[0];

        $.get(service, function (data) {
            var jsonObj = data.ask_items;
            if (jsonObj.length > 0) {

                //qsb_question_active($(second_item).find("select"));
                for (var i = 0; i < jsonObj.length; i++) {

                    var ask_display = jsonObj[i]['showtitle'];
                    var ask_val = jsonObj[i]['showvalue'];
                    var ask_r_val = jsonObj[i]['realvalue'];
                    var alias_url = jsonObj[i]['listing_url'];

                    second_dropdown_map(ask_val, ask_r_val, alias_url, question_level, first_qq);
                    if (lasteventObj != undefined) {
                        $(second_item).find("select").append('<option value="' + get_val_2(ask_val, ask_r_val, question_level) + '" isid="' + ask_r_val + '">' + ask_display + '</option>');
                        //if this dropdown depends on last dropdown to display, then once it has more than one items, it should display.
                        var display_select = true;

                        if ($(second_item).find("select option").length >= 2 && display_select) {

                            qsb_question_select(lasteventObj);

                            display_select = false;
                        }
                    } else
                        $(second_item).find('select').append('<option value="' + get_val_2(ask_val, ask_r_val, question_level) + '" isid="' + ask_r_val + '">' + ask_display + '</option>');

                }
                qsb_question_finish_loading(second_item);
            }
            precheck(second_qq);
        });
    }

    function get_third_dropdown_data(third_item, service, target_type, question_level, lasteventObj) {

        service = service + trailing_slash + "?type=" + target_type;
        service = $.eddy_core.cache_buster.append_cache_buster_qs(service);

        var first_qq = $(third_item).parent().find('li.qsb-question:first').attr("class").split(' ')[0];
        var third_qq = $(third_item).attr("class").split(' ')[0];

        $.get(service, function (data) {

            var jsonObj = data.ask_items;

            if (jsonObj != null && jsonObj.length > 0) {

                for (var i = 0; i < jsonObj.length; i++) {

                    var ask_display = jsonObj[i]['showtitle'];
                    var ask_val = jsonObj[i]['showvalue'];
                    var ask_r_val = jsonObj[i]['realvalue'];
                    var alias_url = jsonObj[i]['listing_url'];


                    third_dropdown_map(ask_val, ask_r_val, alias_url, question_level, first_qq);

                    if (lasteventObj != undefined) {
                        //no show subject items if it's going to listing page and alias_url is empty
                        if ((($('.qdf-holder form').attr("target-type") == 'qdf-listing') && (alias_url != "")) || (($('.qdf-holder form').attr("target-type") == 'qdf-listing')) || ($('.qdf-holder form').attr("target-type") != 'qdf-listing'))
                            //if((($('.qdf-holder form').attr("target-type") == 'qdf-listing') && (alias_url != "")) || ($('.qdf-holder form').attr("target-type") != 'qdf-listing'))
                            $(third_item).find("select").append('<option value="' + get_val_3(ask_val, ask_r_val, question_level) + '" isid="' + ask_r_val + '">' + ask_display + '</option>');

                        var display_select = true;
                        if (($(third_item).find("select option").length >= 2) && display_select) {

                            qsb_question_select($(lasteventObj));
                            display_select = false;
                        }
                    } else
                        $(third_item).find('select').append('<option value="' + get_val_3(ask_val, ask_r_val, question_level) + '" isid="' + ask_r_val + '">' + ask_display + '</option>');

                }
                qsb_question_finish_loading(third_item);
            }
            precheck(third_qq);
        });
    }


    // the value show in dropdown option value mapping to the value pass to IS web service
    function first_dropdown_map(ask_val, ask_r_val, alias_url, question_level, first_qq) {
        first_dropdown_mapping[first_qq][question_level][ask_val] = {};
        first_dropdown_mapping[first_qq][question_level][ask_val][0] = ask_r_val;
        first_dropdown_mapping[first_qq][question_level][ask_val][1] = alias_url;
    }

    function second_dropdown_map(ask_val, ask_r_val, alias_url, question_level, first_qq) {
        second_dropdown_mapping[first_qq][question_level][ask_val] = {};
        second_dropdown_mapping[first_qq][question_level][ask_val][0] = ask_r_val;
        second_dropdown_mapping[first_qq][question_level][ask_val][1] = alias_url;
    }

    function third_dropdown_map(ask_val, ask_r_val, alias_url, question_level, first_qq) {
        third_dropdown_mapping[first_qq][question_level][ask_val] = {};
        third_dropdown_mapping[first_qq][question_level][ask_val][0] = ask_r_val;
        third_dropdown_mapping[first_qq][question_level][ask_val][1] = alias_url;
    }


    function get_listing_url(first_field, second_field, third_field, question_level, first_qq) {
        var url = "";

        if (third_field != "-1" && third_field != "") {

            url = third_dropdown_mapping[first_qq][question_level][third_field][1];

        } else if (second_field != "-1") {
            url = second_dropdown_mapping[first_qq][question_level][second_field][1];
        } else {
            url = first_dropdown_mapping[first_qq][question_level][first_field][1];
        }

        return url;
    }

    function get_query_string(formObj, question_level, first_qq) {

        var query_string_format = {};
        query_string_format['Category'] = {};
        query_string_format['EduLevel'] = {};

        query_string_format['Category'][0] = "?Categories=" + formObj.find('li.Category select :selected').attr("isid") + "&SubCategories=" + formObj.find('li.Subject select :selected').attr("isid");
        query_string_format['Category'][1] = "?level=" + formObj.find('li.EduLevel select :selected').attr("isid") + "&Categories=" + formObj.find('li.Category select :selected').attr("isid") + "&SubCategories=" + formObj.find('li.Subject select :selected').attr("isid");
        query_string_format['EduLevel'][1] = "?level=" + formObj.find('li.EduLevel select :selected').attr("isid") + "&category=" + formObj.find('li.Category select :selected').attr("isid") + "&subject=" + formObj.find('li.Subject select :selected').attr("isid");
        return query_string_format[first_qq][question_level];
    }

    function get_query_string_for_listing(formObj, question_level, first_qq) {

        var query_string_format = {};
        query_string_format['Category'] = {};
        query_string_format['EduLevel'] = {};

        query_string_format['Category'][0] = "?category=" + formObj.find('li.Category select :selected').attr("isid") + "&subject=" + formObj.find('li.Subject select :selected').attr("isid");
        query_string_format['Category'][1] = "?level=" + formObj.find('li.EduLevel select :selected').attr("isid") + "&category=" + formObj.find('li.Category select :selected').attr("isid") + "&subject=" + formObj.find('li.Subject select :selected').attr("isid");
        query_string_format['EduLevel'][1] = "?level=" + formObj.find('li.EduLevel select :selected').attr("isid") + "&category=" + formObj.find('li.Category select :selected').attr("isid") + "&subject=" + formObj.find('li.Subject select :selected').attr("isid");

        return query_string_format[first_qq][question_level];
    }

    //preselect dropdown if preche_filter field is checked
    function precheck(name) {
        var eddy_request_name = name;

        if (name == 'EduLevel')
            eddy_request_name = 'Level';
        if (Drupal.settings.prechk_filter) {

            if (Drupal.settings.prechk_filter_options != undefined && Drupal.settings.prechk_filter_options.hasOwnProperty(eddy_request_name.toLowerCase())) {

                var item = Drupal.settings.prechk_filter_options[eddy_request_name.toLowerCase()];

                if (item.length > 0) {
                    var selected = item[0];
                    if (name == 'EduLevel') {
                        $.each(item, function (key, value) {
                            if (key != 0)
                                selected += "," + value;
                        });
                    }

                    $('li.' + name + ' select option[isid="' + selected + '"]').prop('selected', true);
                    //$('li.' + name + ' select').val('Business');

                    $('li.' + name + ' select').trigger('change');


                }
            }


        }


    }


})(jQuery);

