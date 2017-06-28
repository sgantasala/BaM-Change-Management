<div class="sab-school-details clearfix row">
    eddy_build_institution_logo($details->schoolDetails, '120', array('link' => null, 'linkTitle' => 'Learn more about ' . $details->schoolDetails->InstitutionName, 'attributes' => array('itemprop' => 'logo')))
    <div class="logo-holder-details col-xs-12">
        <?php if(arg(0) == 'node' && !$details->schoolDetails->FailedValidation) : ?>
        <?php print eddy_build_institution_logo($details->schoolDetails, '240', array('link' => null, 'linkTitle' => 'Learn more about ' . $details->schoolDetails->InstitutionName, 'attributes' => array('itemprop' => 'logo'))); ?>
        <?php elseif($details->schoolDetails->FailedValidation): ?>
        <?php print eddy_build_institution_logo($details->schoolDetails, '240', array('link' => null, 'linkTitle' => 'Learn more about ' . $details->schoolDetails->InstitutionName, 'attributes' => array('itemprop' => 'logo'))); ?>
        <?php else: ?>
        <?php print eddy_build_institution_logo($details->schoolDetails, '240', array('link' => 'node/' . $details->schoolDetails->entity_id, 'linkTitle' => 'Learn more about ' . $details->schoolDetails->InstitutionName, 'attributes' => array('itemprop' => 'logo'))); ?>
        <?php endif; ?>
    </div>

    <?php if(!$details->schoolDetails->FailedValidation):?>

    <div class="sab-school-detail-description col-xs-12">
        <?php print count($details->programDetails) . '---' . $details->schoolDetails->InstitutionDescription; ?>
    </div>

    <?php if(!empty($details->programDetails) && count($details->programDetails) >0 ):?>
    <div class="row sab-school-program-items">
        <div class="sab-school-detail-program-head col-xs-12">
            Programs from <?php print $details->schoolDetails->InstitutionName; ?>
        </div>

        <ul class="sab-school-programs col-xs-12">
            <?php foreach($details->programDetails as $index=>$program) { ?>

            <?php if($index == 9): ?>
            <ul class="collapse col-xs-12 view-more-sab-school-programs" id="view-more-sab-school-programs">
                <?php endif; ?>

                <li class="sab-school-program-item">
                    <div class="sab-school-program-details content-item-holder clearfix">
                        <div class="sab-school-program-logo logo-holder col-xs-2">
                            <?php print sab_listing_logo_link(eddy_build_institution_logo($program, "120", array('link' => NULL, 'linkTitle' => '', 'attributes' => array('itemprop' => 'logo'))), $program); ?>
                        </div>
                        <div class="sab-school-program-detail-left content-item col-xs-8">
                            <div class="sab-school-program-title">
                                <?php print $program->ProgramName;
                                ?>
                            </div>
                            <div class="sab-schoolprogram-desc">
                                <?php print $program->ProgramDescription; ?>
                            </div>
                        </div>
                        <div class="sab-school-program-detail-button-holder col-xs-2">
                            <div class="sab-school-program-rating">
                                *******
                            </div>
                            <div class="learn-more">
                                <a href="<?php //print $details->form_url; ?>">LEARN MORE</a>
                            </div>
                        </div>
                    </div>

                </li>

                <?php } ?>

                <?php if(count($details->programDetails) > 10): ?>
            </ul>
            <?php endif; ?>
        </ul>
        <?php if(count($details->programDetails) > 10): ?>
            <div class="sab-show-program-count col-xs-12">
                ----- <span class="sab-program-display-count">10</span> of <span class="sab-program-total-count"><?php print count($details->programDetails); ?></span> -----
            </div>
            <div class="view-more-sab-programs col-xs-12 collapsed" data-toggle="collapse" data-target="#view-more-sab-school-programs">
                <span class="learn-more"></span>
            </div>
        <?php else :?>
            <div class="sab-show-program-count col-xs-12">
                ----- <?php print count($details->programDetails); ?> of <?php print count($details->programDetails); ?> -----
            </div>
        <?php  endif; ?>
    </div>
    <?php endif;?>



    <?php endif; ?>
</div>
<!--/.details-school-header--> 