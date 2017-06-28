<?php if($list_fields->user_change_records): ?>
<div class="results-count-holder">
    <ul>
        <li class="results-view">View: </li>
        <li>
            <a class="results-25" href="#">25</a>
        </li>
        <li>
            <a class="results-50" href="#">50</a>
        </li>
        <li>
            <a class="results-100" href="#">100</a>
        </li>
    </ul>
</div>
<?php endif;?>

<?php if($list_fields->show_pager && ($list_fields->show_pager_location == 'both' || $list_fields->show_pager_location == 'top')): ?>
<div class="pager-container">
    <?php print $pager;?>
</div>
<?php endif;?>

<ul id="<?php print $list_fields->machine_name ?>" class="eddy-listings eddy-school-listings <?php print $list_fields->machine_name ?> clearfix">
    <?php
    foreach ($matching_list as $inIndex => $inData):
        $formURL = '/form/' . $inData->InstitutionId;

        $firstProgram = $inData->ProgramList[0];

        //Removes First Item from Array.
        array_shift($inData->ProgramList);

    ?>

    <li class="<?php print $inData->classes; ?> clearfix">
        <?php if ($list_fields->show_school_logo): ?>
        <div class="logo-holder">
            <?php

                //PaidStatusTypeId
                //1    Free
                //2    Fraid
                //3    Paid
                //6    PaidClicks

                if($firstProgram->PaidStatusTypeId != 1){
                    $logoTitle = 'Learn about ' . $inData->InstitutionName;
                    print sab_listing_institution_details_link(eddy_build_institution_logo($firstProgram, eddy_listing_convert_logo_size($list_fields), array('link' => NULL, 'linkTitle' => $logoTitle)), $inData);
                }
            ?>
        </div>
        <?php endif ?>

        <?php if ($list_fields->show_school_title): ?>
        <h3>
            <?php print sab_listing_institution_details_link($inData->InstitutionName, $inData, array('title' => 'Learn more about '.$inData->InstitutionName)); ?>
        </h3>
        <?php endif; ?>

        <?php if($list_fields->show_school_description || $list_fields->show_school_title || $list_fields->show_request_info_button): ?>

        <div class="content-item-holder">
            <?php if ($list_fields->show_school_description || $list_fields->show_school_title): ?>
            <div class="content-item">
                <?php if ($list_fields->show_school_description): ?>
                <p>
                    <?php print strip_tags($inData->description) ?>
                </p>
                <?php endif ;?>
            </div>
            <?php endif ;?>
            <?php if($list_fields->show_school_info_button || $list_fields->show_request_info_button): ?>
            <div class="button-holder">


                <?php if ($list_fields->show_school_info_button): ?>
                <a title="Learn more about <?php print $inData->InstitutionName; ?>" class="button-school-info" href="<?php print $formURL; ?>">School Info</a>
                <?php endif; ?>


                <?php if ($list_fields->show_request_info_button && !$inData->FailedValidation): ?>
                <a title="Request free information from <?php print $inData->InstitutionName; ?>" class="button-request-info" href="<?php print get_eddy_form_url_by_institution_program_id($inData->InstitutionId); ?>">Request Info</a>
                <?php endif; ?>


            </div>
            <?php endif; ?>
        </div>
        <?php endif; ?>

        <?php if($list_fields->show_nested_programs):?>

        <h4>
            <?php print eddy_listing_details_link($firstProgram->ProgramName, $firstProgram); ?>
        </h4>
        <p>
            <?php
                  $firstProgram->ProgramDescription = strip_tags($firstProgram->ProgramDescription); // Removes HTML from Description
                  print text_summary($firstProgram->ProgramDescription, null, 200);
            ?>
        </p>

        <?php if ($list_fields->show_nested_programs && isset($inData->CampusList)): //If an Institution has nested Campuses ?>

        <ul class="eddy-listings eddy-campus-listings">

            <?php foreach($inData->CampusList as $caIndex => $caData): ?>

            <li class="listing-row clearfix">
                <?php if($caData->CampusType == 2): ?>
                <?php
					    $CampusAddress = "";
					    if(!empty($caData->State)){
						    $CampusAddress = $caData->City . ', ' . $caData->State;
					    }
                ?>
                <div class="left-address">
                    <?php print $CampusAddress ?>
                </div>
                <?php else: ?>
                <div class="left-address">Online</div>
                <?php endif; ?>

                <?php if ($list_fields->show_nested_programs && isset($caData->ProgramList)): ?>

                <ul class="eddy-listings eddy-program-listings aggregation-list-view-more" style="display:none;">

                    <?php foreach($caData->ProgramList as $program): ?>
                    <li class="listing-row clearfix ">

                        <div class="content-item-holder">
                            <div class="content-item">
                                <h3>
                                    <a href="<?php print eddy_listing_request_url($program); ?>">
                                        <?php print $program->ProgramName; ?>
                                    </a>
                                </h3>
                            </div>
                            <?php if($list_fields->show_request_info_button && !$program->FailedValidation): ?>
                            <div class="button-holder clearfix">
                                <a class="button-request-info" href="<?php print eddy_listing_request_url($program); ?>">Request Info</a>
                            </div>
                            <?php endif; ?>
                        </div>

                    </li>
                    <?php endforeach; ?>

                </ul>

                <?php if($caData->ProgramCount > 0): ?>
                <div class="view-additional-holder">
                    <?php print l($caData->ProgramCount . " Additional Program(s) Available", $_GET['q']); ?>
                </div>
                <?php endif; ?>

                <?php endif; ?>
            </li>
            <?php endforeach; ?>
        </ul>

        <?php elseif ($list_fields->show_nested_programs && isset($inData->ProgramList)): //If an Institution has nested Programs only ?>

        <ul class="eddy-listings eddy-program-listings aggregation-list-view-more" style="display:none;">

            <?php foreach($inData->ProgramList as $program): ?>

            <li class="listing-row clearfix ">

                <div class="content-item-holder">
                    <div class="content-item">
                        <h3>
                            <a href="<?php print eddy_listing_request_url($program); ?>">
                                <?php print $program->ProgramName; ?>
                            </a>
                        </h3>
                    </div>
                    <?php if($list_fields->show_request_info_button && !$program->FailedValidation): ?>
                    <div class="button-holder clearfix">
                        <a class="button-request-info" href="<?php print eddy_listing_request_url($program); ?>">Request Info</a>
                    </div>
                    <?php endif; ?>
                </div>

            </li>

            <?php endforeach; ?>

        </ul>

        <?php if($inData->ProgramCount > 1): ?>

        <div class="view-additional-holder">
            <?php print l(($inData->ProgramCount) -1 . ' Additional Program(s) Available', $_GET['q']); ?>
        </div>

        <?php endif; ?>

        <?php endif; ?>

        <?php endif; ?>

    </li>
    <?php endforeach; ?>
</ul>

<?php if($list_fields->show_pager && ($list_fields->show_pager_location == 'both' || $list_fields->show_pager_location == 'bottom')): ?>
<div class="pager-container">
    <?php print $pager;?>
</div>
<?php endif;?>