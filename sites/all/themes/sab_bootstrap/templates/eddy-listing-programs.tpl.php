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

<ul class="eddy-listings eddy-program-listings <?php print $list_fields->machine_name ?>">

    <?php
    foreach ($matching_list as $index => $data):
        $ProgramLinkTitle = $data->ProgramName;
        $ProgramLink = eddy_listing_details_url($data);
        $RequestInfoLink = eddy_listing_request_url($data);
        $SchooolURL = $data->url_alias;
        $SchoolLinkTitle = $data->InstitutionName;
    ?>

    <li class="<?php print $data->classes; ?> clearfix">

        <?php if (($list_fields->show_school_logo && ($data->PaidStatusTypeId != 1))): ?>
        <div class="logo-holder">
            <?php

                if($list_fields->show_school_logo && $data->PaidStatusTypeId != 1){
                    $logoTitle = 'Learn about ' . $data->InstitutionName;
                    print sab_listing_logo_link(eddy_build_institution_logo($data, eddy_listing_convert_logo_size($list_fields), array('link' => NULL, 'linkTitle' => $logoTitle)), $data);
                }

            ?>
        </div>
        <?php endif; ?>

        <div class="content-item-holder">

            <?php if ($list_fields->show_school_title): ?>
            <h4>
                <a href="<?php print $RequestInfoLink; ?>">
                    <?php print $data->InstitutionName; ?>
                </a>
            </h4>
            <?php endif; ?>

            <?php if ($list_fields->show_program_title): ?>
            <h3>
                <a title="<?php  print $ProgramLinkTitle ?>" href="<?php  print $ProgramLink ?>">
                    <?php print $data->ProgramName; ?>
                </a>
            </h3>
            <?php endif; ?>

            <div class="content-item">
                <?php if ($list_fields->show_school_description): ?>
                <?php print $data->description; ?>
                <?php endif; ?>
                <?php if ($list_fields->show_program_description): ?>
                <p>
                    <?php print text_summary($data->ProgramDescription, $format = 'program_filter', $size = 200)?>
                    <a href="<?php  print $ProgramLink ?>">more ></a>
                </p>
                <?php endif; ?>
            </div>
            <?php if($list_fields->show_degree_info_button|| $list_fields->show_school_info_button || $list_fields->show_request_info_button): ?>
            <div class="button-holder button-link button-link clearfix">
                <?php if ($list_fields->show_degree_info_button): ?>
                <a title="<?php  print $ProgramLinkTitle ?>" class="button-program-info" href="<?php  print $ProgramLink ?>">
                    <span>
                        <?php print $data->ProgramName; ?>
                    </span>
                    Info
                    <span>
                        from <?php print $data->InstitutionName; ?>
                    </span>
                </a>
                <?php endif; ?>
                <?php if ($list_fields->show_school_info_button): ?>
                <a class="button-school-info" href="<?php print $RequestInfoLink; ?>">
                    <span>
                        <?php print $data->InstitutionName; ?>
                    </span>
                    School Info
                </a>
                <?php endif; ?>
                <?php if ($list_fields->show_request_info_button && !$data->FailedValidation): ?>
                <a title="<?php print $ProgramLinkTitle ?>" class="button-request-info" href="<?php print $RequestInfoLink; ?>">Request Info</a>
                <?php endif; ?>
            </div>
            <?php endif; ?>
        </div>

    </li>
    <?php endforeach; ?>

</ul>

<?php if($list_fields->show_pager && ($list_fields->show_pager_location == 'both' || $list_fields->show_pager_location == 'bottom')): ?>
<div class="pager-container">
    <?php print $pager;?>
</div>
<?php endif;?>