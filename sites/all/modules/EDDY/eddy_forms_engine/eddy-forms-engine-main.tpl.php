<div id="columns-wrapper" class="form">
    <div id="column-wide">
        <?php
        if(!empty($form->program_template_message)){
            print $form->program_template_message;
        }

        print get_eddy_forms_engine_contents();

        $showAbout = "";
        $schoolAccordImg = 'sidebar-collapse.gif';
        if(arg(2) && is_numeric(arg(2))){
            $showAbout = 'no-show';
            $schoolAccordImg = 'sidebar-expand.gif';
        }

        ?>
    </div>

    <div id="column-narrow">

        <div class="school-logo">
            <?php print eddy_build_institution_logo($school, 240, array('link' => NULL, 'linkTitle' => NULL)); ?>
        </div>

        <div id="google_map"></div>

        <div class="right-inc-wrapper-outer">
            <div id="prodesc"></div>
            <div class="right-inc-wrapper-inner">
                <div id="div-program-info" style="display:none">
                    <h3 class="program-info">Program Info</h3>
                    <a id="toggle-program-info-section" class="sidebar-section-link" href="#">
                        <img src="<?php print file_create_url(drupal_get_path('module', 'eddy_forms_engine') . "/images/sidebar-collapse.gif"); ?>" />
                    </a>
                    <p>
                        <span id="program-name" class="program-name"></span>
                        <span id="program-description"></span>
                        <span id="program-disclaimer"></span>
                    </p>
                </div>
                <?php if(!empty($school->Description)): ?>
                <h3 class="about-us">About Us</h3>
                <a id="toggle-about-us-section" class="sidebar-section-link" href="#">
                    <img src="<?php print file_create_url(drupal_get_path('module', 'eddy_forms_engine') . "/images/$schoolAccordImg");  ?>" />
                </a>
                <div class="moreinfo <?php print $showAbout ?>">
                    <?php print $school->Description; ?>
                </div>
                <?php endif; ?>
                <?php if(!empty($school->Accreditation)): ?>
                <h3 class="accreditation">Accreditation</h3>
                <a id="toggle-accreditation-section" class="sidebar-section-link" href="#">
                    <img src="<?php print file_create_url(drupal_get_path('module', 'eddy_forms_engine') . "/images/sidebar-expand.gif"); ?>" />
                </a>
                <div class="moreinfo last no-show">
                    <?php print strip_tags($school->Accreditation, '<p><a><ul><ol><li><em><strong>'); ?>
                </div>
                <?php endif; ?>
            </div>
        </div>

        <div class="right-inc clearfix">

            <?php if(!empty($school->student_quotes)): ?>
            <h4>Student Quotes</h4>
            <?php
                      $quotes = $school->student_quotes;
                      if(strrpos($quotes, '#') === false){
                          print $quotes;
                      }else{
                          $next_to_last = strrpos($quotes, '#', strrpos($quotes, '#')-strlen($quotes)-1);
                          $student_quote = trim(substr($quotes,0,$next_to_last-1),'<p> </p>');
                          $student_name = str_replace('#', '-- ', substr($quotes, $next_to_last, strrpos($quotes, '#')-strlen($quotes)-1));
                          print '<p>"' . $student_quote . '"</p>';
                          print '<p style="float:right; margin-top:0 !important">' . $student_name . '</p>';
                      }
            ?>

            <?php /*
                      <?php elseif(!empty($form->facts)): ?>
                      <h4>eLearners Facts</h4>
                      <?php print $form->facts; ?>
                      <?php else: ?>
                      <?php print variable_get('eddy_forms_engine_global_facts'); ?>
                       */ ?>

            <?php endif; ?>

        </div>
        <?php /*
	    <div class="right-inc-wrapper-outer">
        <div class="right-inc-wrapper-inner">

        <?php if(!empty($school->InstitutionName)): ?>
        <?php $schoolName = $school->InstitutionName; ?>
        <?php else: ?>
        <?php $schoolName = ""; ?>
        <?php endif; ?>

        <?php if(!empty($form->further_info)): ?>
        <?php print str_replace('[school-name]', $schoolName, $form->further_info); ?>
		      <?php else: ?>
			    <?php $further_info = variable_get('eddy_forms_engine_further_info'); ?>
			    <?php print str_replace('[school-name]', $schoolName, variable_get('eddy_forms_engine_further_info')); ?>
		      <?php endif; ?>
		    </div>
	    </div>
	    */ ?>

    </div>
</div>