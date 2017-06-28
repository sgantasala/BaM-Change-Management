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

<ul class="eddy-listings eddy-campus-program-listings <?php print $list_fields->machine_name; ?>">

    <?php foreach ($matching_list as $index => $data): ?>

    <li class="<?php print $data->classes; ?> clearfix" <?php print (!isset($data->node)) ? ' style="background:pink;"' : ''; ?>>

        <?php if ($list_fields->show_school_logo): ?>
        <div class="logo-holder">
            <?php
                  $logoTitle = 'Learn about ' . $data->InstitutionName;
                  print eddy_build_institution_logo($data, eddy_listing_convert_logo_size($list_fields), array('link' => eddy_listing_request_url($data), 'linkTitle' => $logoTitle));
            ?>
        </div>
        <?php endif ?>

        <?php if ($list_fields->show_school_title): ?>

        <h4>
            <?php print $data->InstitutionName; ?>
        </h4>

        <?php endif; ?>

        <?php if($list_fields->show_school_description || $list_fields->show_school_title || $list_fields->show_request_info_button): ?>

        <div class="content-item-holder">

            <?php if($list_fields->show_school_description): ?>
            <div class="content-item">
                <?php if ($list_fields->show_school_description): ?>
                <p>
                    <?php print strip_tags($data->description) ?>
                    <a href="<?php print eddy_listing_request_url($data); ?>">more ></a>
                </p>
                <?php endif ;?>
            </div>
            <?php endif; ?>

            <?php if($list_fields->show_school_info_button || $list_fields->show_request_info_button): ?>
            <div class="button-holder">
                <?php if ($list_fields->show_school_info_button): ?>
                <a title="Learn more about <?php print $data->InstitutionName; ?>" class="button-school-info" href="<?php print eddy_listing_request_url($data); ?>">School Info</a>
                <?php endif; ?>
                <?php if ($list_fields->show_request_info_button && !$data->FailedValidation): ?>
                <a title="Request free information from <?php print $data->InstitutionName; ?>" class="button-request-info" href="<?php print eddy_listing_request_url($data); ?>">Request Info</a>
                <?php endif; ?>
            </div>
            <?php endif; ?>

        </div>

        <?php endif; ?>

        <?php if ($list_fields->show_nested_programs && $data->ProgramCount > 0): ?>

        <ul class="eddy-listings eddy-campus-program-listings aggregation-list-view-more" style="display:none;">

            <?php
                  foreach($data->ProgramList as $program):
                      $program->InstitutionId = $data->InstitutionId;
            ?>

            <li>

                <h3>
                    <?php print eddy_listing_details_link($program->ProgramName, $program); ?>
                </h3>

                <?php if($list_fields->show_degree_info_button || $list_fields->show_school_info_button || $list_fields->show_request_info_button): ?>

                <div class="button-holder clearfix">
                    <?php if ($list_fields->show_degree_info_button): ?>
                    <?php print eddy_listing_details_link("Read More", $program); ?>
                    <?php endif; ?>
                    <?php if ($list_fields->show_degree_info_button): ?>
                    <?php print eddy_listing_details_link("Visit Site", $program); ?>
                    <?php endif; ?>
                    <?php if ($list_fields->show_request_info_button && !$program->FailedValidation): ?>
                    <?php print eddy_listing_request_link("Request Info", $program); ?>
                    <?php endif; ?>
                </div>

                <?php endif; ?>

            </li>

            <?php endforeach; ?>

        </ul>

        <div class="view-additional-holder">
            <?php print l(($data->ProgramCount) . ' Additional Program(s) Available', current_path()); ?>
        </div>

        <?php endif; ?>

    </li>

    <?php endforeach; ?>

</ul>

<?php if($list_fields->show_pager && ($list_fields->show_pager_location == 'both' || $list_fields->show_pager_location == 'bottom')): ?>
<div class="pager-container">
    <?php print $pager;?>
</div>
<?php endif; ?>