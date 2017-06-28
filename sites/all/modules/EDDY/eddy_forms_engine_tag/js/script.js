var FormsEngine = FormsEngine || {};

(function ($) {

    $(document).ready(function () {

        if (window.Drupal && Drupal.hasOwnProperty('settings') && $("#eddy-form-container").hasClass("stand-alone-form")) {

            is_wizard = true;

            if (Drupal.settings.hasOwnProperty('program_details')) {

                if (Drupal.settings.program_details.hasOwnProperty('institution_name')) {

                    FormsEngine.InstitutionName = Drupal.settings.program_details.institution_name;

                }

                if (Drupal.settings.program_details.hasOwnProperty('institution_id')) {

                    FormsEngine.InstitutionId = Drupal.settings.program_details.institution_id;

                }

                if (Drupal.settings.program_details.hasOwnProperty('program_id')) {

                    FormsEngine.ProgramId = Drupal.settings.program_details.program_id;

                }

            }

            if (FormsEngine.hasOwnProperty('InstitutionId') && !FormsEngine.hasOwnProperty('TemplateId')) {
                is_wizard = false;
            }

            if (is_wizard) {

                $("#eddy-form-container").attr('name', 'eddy-form-container').addClass('eddy-form-container');

            }

            //Loads JQuery Validate if it is not present.
            if (typeof $.fn.validate !== "function") {

                $.getScript("https://ajax.aspnetcdn.com/ajax/jquery.validate/1.11.1/jquery.validate.min.js");

            }

            //Loads jQuery Cookie if it is undefined.
            if ($.cookie == "undefined" || $.cookie == undefined) {

                $.getScript("https://cdnjs.cloudflare.com/ajax/libs/jquery-cookie/1.4.1/jquery.cookie.js");

            }

            //Builds FE Object

            //Sets Default Rendering Strategy
            if (!FormsEngine.hasOwnProperty('RenderingStrategy')) {

                if (is_wizard) {
                    FormsEngine.RenderingStrategy = 'WIZARDPROFESSIONALBOOTSTRAP';
                } else {
                    FormsEngine.RenderingStrategy = 'Original';
                }

            }

            if (!FormsEngine.hasOwnProperty('Theme')) {
                FormsEngine.Theme = "default";
            }

            FormsEngine.AdditionalFields = FormsEngine.AdditionalFields || [];

            //Sets Wizard Specific Properties

            if (is_wizard) {

                //Sets Default Template Id
                if (!FormsEngine.hasOwnProperty('TemplateId')) {
                    FormsEngine.TemplateId = 252;
                }

                FormsEngine.EnablejQueryUI = false;
                FormsEngine.SelfContained = true;
                FormsEngine.SessionId = ($.cookie('_Session')) ? $.cookie('_Session') : "00000000-0000-0000-0000-0000-000000000000";
                FormsEngine.CompressJs = false;

                FormsEngine.AdditionalFields.push(['Form Type', 'Wizard']);
                FormsEngine.AdditionalFields.push(['FETemplate', FormsEngine.TemplateId]);

                if (FormsEngine.hasOwnProperty('WorkflowManagedChoicePage') && FormsEngine.hasOwnProperty('WorkflowThankYouPage') && FormsEngine.hasOwnProperty('WorkflowNoMatchPage')) {

                    FormsEngine.SelfContained = false;

                    FormsEngine.WorkflowStartPage = location.href;
                    FormsEngine.WorkflowManagedChoicePage = fe_tag_append_query_strings(FormsEngine.WorkflowManagedChoicePage);
                    FormsEngine.WorkflowThankYouPage = fe_tag_append_query_strings(FormsEngine.WorkflowThankYouPage);
                    FormsEngine.WorkflowNoMatchPage = fe_tag_append_query_strings(FormsEngine.WorkflowNoMatchPage);

                    FormsEngine.ConsumerSideWorkflowStep = 'START';

                }

            } else {
                FormsEngine.ThankYouPage = '/form/thank-you';
                FormsEngine.AdditionalFields.push(['Form Type', 'Program Template']);
            }

            FormsEngine.RenderingDiv = 'eddy-form-container';
            FormsEngine.IsBeta = false;
            FormsEngine.TrackId = ($.cookie('_CampaignTrackID')) ? $.cookie('_CampaignTrackID') : "F225C16D-5469-4877-BA17-6D79F9944EDB";

            if (Drupal.settings.hasOwnProperty('application_id')) {
                FormsEngine.ApplicationId = Drupal.settings.application_id;
                if (Drupal.settings.hasOwnProperty('application_name') && Drupal.settings.application_id == '7') {
                    FormsEngine.ApplicationName = Drupal.settings.application_name.toUpperCase();
                }
            } else {
                FormsEngine.ApplicationId = 16; //Sets it to Microsites if not specified.
            }

            FormsEngine.MatchResponseGuid = ($.cookie('MatchResponseGuid') ? $.cookie('MatchResponseGuid') : "00000000-0000-0000-0000-0000-000000000000");

            FormsEngine.AdditionalFields.push(['FERenderingStrategy', FormsEngine.RenderingStrategy]);
            FormsEngine.AdditionalFields.push(['FETheme', FormsEngine.Theme]);

            //Resets Workflow to Start by default.
            if (!FormsEngine.hasOwnProperty('ResetWorkflow')) {
                FormsEngine.ResetWorkflow = true;
            }

            if (is_wizard) {

                $.getScript(Drupal.settings.form_engine_url + "/Static/GetBundledWizardJs", function (data, textStatus, jqxhr) {

                    FormsEngine.LoadForm();

                });

            } else {

                $.getScript(Drupal.settings.form_engine_url + "/Static/GetGlobal", function (data, textStatus, jqxhr) {

                    if (jqxhr.status == 200) {
                        $.getScript(Drupal.settings.form_engine_url + "/Static/GetClient");
                    }

                });

            }

        }

    });

    function fe_tag_append_query_strings(value) {

        var path = location.pathname.replace(/^\/|\/$/g, '');

        if (value.indexOf("?") == -1) {

            value += "?form_start_page=" + path;

        } else {

            value += "&form_start_page=" + path;

        }

        return value;

    }

})(jQuery);