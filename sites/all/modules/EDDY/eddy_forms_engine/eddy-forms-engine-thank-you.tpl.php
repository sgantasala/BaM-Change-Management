<?php $app_name = str_replace("_","",variable_get("eddy_core_application_name"));?>
<div id="column-wide">
    <?php/* // if($_GET['IsAnyLeadValid'] == "1"):
	print variable_get('thank_you_success_lead_msg');
   //else:
	print variable_get('thank_you_failed_lead_msg');
  //endif; */?>
    <div id="thank-you-message"></div>
    <div id="UserSelections"></div>
    <div class="ty-page">
        <div class="clearfix">
            <?php if(!empty($form->set_yourself_up)): ?>
            <?php print $form->set_yourself_up; ?>
            <?php else: ?>
            <?php
                      if(variable_get('thank_you_content_1') != NULL){
                          $content_1 = variable_get('thank_you_content_1');
                          print $content_1['value'];
                      }
            ?>
            <?php endif; ?>
        </div>

    </div>
</div>
