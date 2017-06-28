function form_wizard_change_workflow(data){

	function getQuerystring(key, default_) {
		if (default_ == null) default_ = "";
		key = key.replace(/[\[]/, "\\\[").replace(/[\]]/, "\\\]");
		var regex = new RegExp("[\\?&]" + key + "=([^&#]*)");
		var qs = regex.exec(window.location.href);
		if (qs == null)
			return default_;
		else
			return qs[1];
	}

	if(!jQuery("body").hasClass("persist-content")){
		
		switch(data){
			case 'START':
				// jQuery(".workflow-container").not("#form-content-container").hide();
				// jQuery("#form-content-container").show();
			break;
			case 'MANAGEDCHOICE':
				// if(jQuery("#managedchoice-container").text().trim() != ''){
					// jQuery(".workflow-container").hide();
					// jQuery("#managedchoice-container").fadeIn(500);
				// }
			break;
			case 'THANKYOU':
				// if(jQuery("#thankyou-container").text().trim() != ''){
					// jQuery(".workflow-container").hide();
					// jQuery("#thankyou-container").fadeIn(500);
				// }
			break;
			case 'NOTHANKYOU':
				// if(jQuery("#nothankyou-container").text().trim() != ''){
					// jQuery(".workflow-container").hide();
					// jQuery("#nothankyou-container").fadeIn(500);
				// }
			break;
			case 'NOMATCH':			
				
				// if(jQuery("#nomatch-container").text().trim() != ''){
					// jQuery(".workflow-container").hide();
					// jQuery("#nomatch-container").fadeIn(500);
				// }
				
				jQuery("#nomatch_clicksnet_listing").html("");
			
				var webservice = Drupal.settings.basePath + "eddy_clicksnet/get_html/?implementation=no_match&wizardprof=true";

				jQuery.get(webservice, function (data) {	
					
					jQuery("#nomatch_clicksnet_listing").html(data);
				
				});

				jQuery('head').append('<link href="http://education-match.com/assets/educationconnection/003/css/clicksnet_style_ec.css" type="text/css" rel="stylesheet" />');
				jQuery('head').append('<link href="http://ads.fcmrktplace.com/css/clix.css" type="text/css" rel="stylesheet" />');
				jQuery('head').append('<link href="http://ads.fcmrktplace.com/css/education/education3.css" type="text/css" rel="stylesheet" />');
				jQuery('head').append('<link href="' + Drupal.settings.basePath + 'sites/all/modules/EDDY/eddy_clicksnet/css/clicksnet_nomatch.css" type="text/css" rel="stylesheet" />');
				jQuery('head').append('<meta content="width=device-width" name="viewport">');
				jQuery('head').append('<meta content="telephone=no" name="format-detection">');

			break;
			default:
				// jQuery(".workflow-container").hide();
				// jQuery(".form-content-container").fadeIn(500);
		}
		
		if (typeof form_wizard_change_workflow_theme == 'function') { 
		  form_wizard_change_workflow_theme(data); 
		}
		
		
	}
	
	//Sets Tracking Params when no trackid is passed in the URL. This is for Other Scripts to Read.
	// if(!jQuery.cookie('_CampaignTrackID') && Drupal.settings.form_wizard.track_id != ""){
		// jQuery.cookie('_CampaignTrackID', Drupal.settings.form_wizard.track_id, { path: '/' });
	// }
	
	
}