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

    <?php if(5 == $inIndex && arg(0) == 'eddy-listing-ajax'): ?>
        
        <li id="gpt-ad-listing-x92" class="listing-row eddy-listings-ad hidden-xs hidden-sm">

             <!-- /59026966/SAB_x92 -->
            <div id='div-gpt-ad-1471369578424-29' class='x92'>
                <script type="text/javascript">
                    if (window.googletag && googletag.apiReady) {

                        googletag.cmd.push(function () {
                            googletag.defineSlot('/59026966/SAB_x92', [468, 60], 'div-gpt-ad-1471369578424-29').addService(googletag.pubads());
                        });

                        googletag.cmd.push(function () { googletag.display('div-gpt-ad-1471369578424-29'); });
                    }
                </script>
            </div>

        </li>
        <li id="gpt-ad-listing-x90" class="listing-row eddy-listings-ad hidden-md hidden-lg">

            <!-- /59026966/SAB_x90 -->
            <div id='div-gpt-ad-1471369578424-27' class='x90'>
                <script type="text/javascript">
                    if (window.googletag && googletag.apiReady) {

                        googletag.cmd.push(function () {
                            googletag.defineSlot('/59026966/SAB_x90', [320, 50], 'div-gpt-ad-1471369578424-27').addService(googletag.pubads());
                        });
                
                        googletag.cmd.push(function () { googletag.display('div-gpt-ad-1471369578424-27'); });

                    }
                </script>
            </div>

        </li>

    <?php endif; ?>

    <li class="<?php print $inData->classes; ?> clearfix">
        <div class="row">
            <?php if (($list_fields->show_school_logo && ($firstProgram->PaidStatusTypeId != 1)) || (sab_listing_institution_details_link("", $inData) != '')): ?>
            <div class="logo-holder col-xs-2">
                <?php

                //PaidStatusTypeId
                //1    Free
                //2    Fraid
                //3    Paid
                //6    PaidClicks

                if($list_fields->show_school_logo && $firstProgram->PaidStatusTypeId != 1){

                    $logoTitle = 'Learn about ' . $inData->InstitutionName;
                    print sab_listing_logo_link(eddy_build_institution_logo($firstProgram, eddy_listing_convert_logo_size($list_fields), array('link' => NULL, 'linkTitle' => $logoTitle)), $firstProgram);
                }

                if(template_sab_listing_institution_details_link("", $inData) != ''):

                ?>
                <div class="view-all button-link">
                    <?php print template_sab_listing_institution_details_link("VIEW ALL PROGRAMS FROM THIS PROVIDER", $inData); ?>
                </div>
                <?php
                endif;
                ?>

            </div>
            <div class="listing-info-container col-xs-10 clearfix">
            <?php else:  ?>
            <div class="listing-info-container col-xs-12 clearfix">
            <?php endif; ?>


            <!--<div class="listing-info-container col-xs-12 clearfix">-->

                <?php if ($list_fields->show_school_title): ?>
                <h3>
                    <?php print template_sab_listing_institution_details_link($inData->InstitutionName, $inData, array('title' => 'Learn more about '.$inData->InstitutionName)); ?>
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

                <div class="programdata clearfix">
                    <div class="row">
                        <h4 class="program-name col-xs-9">
                            <?php print sab_listing_details_link($firstProgram->ProgramName, $firstProgram); ?>
                        </h4>
                        <div class="avg-rating col-xs-3">
                            <?php print (isset($firstProgram->avg_rating))?template_get_avg_rating_html($firstProgram->avg_rating):'';?>
                        </div>
                    </div>
                    <div class="row">
                        <p class="program-desc col-xs-9 hidden-xs">
                            <?php print strip_tags($firstProgram->ProgramShortDescription); ?>
                        </p>
                        <div class="learn-more button-link col-xs-3">
                            <?php print eddy_listing_details_link("LEARN MORE", $firstProgram); ?>
                        </div>
                    </div>
                </div>

                <?php endif; ?>

            </div>
        </div>


        <?php if($list_fields->show_nested_programs):?>
        <div class="additional-eddy-listings-container">
            <?php if ($list_fields->show_nested_programs && isset($inData->CampusList)): //If an Institution has nested Campuses ?>

            <ul class="eddy-listings eddy-campus-listings ">

                <?php foreach($inData->CampusList as $caIndex => $caData): ?>

                <li class="listing-row clearfix">

                    <?php if ($list_fields->show_nested_programs && isset($caData->ProgramList)): ?>

                    <ul class="eddy-listings eddy-program-listings aggregation-list-view-more " style="display:none;">
                        <p>
                            Other Programs from <?php print $inData->InstitutionName; ?> matching this criteria:
                        </p>
                        <?php foreach($caData->ProgramList as $program): ?>
                        <li class="listing-row clearfix ">

                            <div class="content-item-holder">
                                <div class="content-item">
                                    <h3 class="program-name">
                                        <?php print eddy_listing_details_link($program->ProgramName, $program); ?>
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
                        <i class="fa fa-long-arrow-down" aria-hidden="true"></i>
                        <?php print l("VIEW OTHER MATCHING " . strtoupper($inData->InstitutionName) . " PROGRAMS", $_GET['q']); ?>
                        <i class="fa fa-long-arrow-down" aria-hidden="true"></i>
                    </div>
                    <?php endif; ?>

                    <?php endif; ?>
                </li>
                <?php endforeach; ?>
            </ul>

            <?php elseif ($list_fields->show_nested_programs && isset($inData->ProgramList)): //If an Institution has nested Programs only ?>

            <ul class="eddy-listings eddy-program-listings aggregation-list-view-more " style="display:none;">
                <p>
                    Other Programs from <?php print $inData->InstitutionName; ?> matching this criteria:
                </p>
                <?php foreach($inData->ProgramList as $program): ?>

                <li class="listing-row clearfix ">

                    <div class="content-item-holder">
                        <div class="content-item">
                            <h3 class="program-name">
                                <?php print eddy_listing_details_link($program->ProgramName, $program); ?>
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
                <i class="fa fa-long-arrow-down" aria-hidden="true"></i>
                <?php print l("VIEW OTHER MATCHING " . strtoupper($inData->InstitutionName) . " PROGRAMS", $_GET['q']); ?>
                <i class="fa fa-long-arrow-down" aria-hidden="true"></i>
            </div>

            <?php endif; ?>

            <?php endif; ?>
        </div>
        <?php endif; ?>

    </li>
    <?php endforeach; ?>
</ul>

<?php if($list_fields->show_pager && ($list_fields->show_pager_location == 'both' || $list_fields->show_pager_location == 'bottom')): ?>
<div class="pager-container">
    <?php print $pager;?>
</div>
<?php endif;?>