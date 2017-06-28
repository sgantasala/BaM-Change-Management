<div class="row eddy-listings eddy-program-listings <?php print $list_fields->machine_name ?>">
    <div class="sab-school-detail-program-head">
        Similar Trending Programs
    </div>
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
    <div  class="pager-container">
        <?php print $pager;?>
    </div>
    <?php endif;?>
    <?php foreach ($matching_list as $index => $data):
              
                $ProgramLinkTitle = $data->ProgramName;
        $ProgramLink = eddy_listing_details_url($data);
        $RequestInfoLink = eddy_listing_request_url($data);
    ?>
    <div class="col-sm-6 col-md-4">

        <div class="thumbnail" style="background-image: url(<?php print get_program_image_path($data); ?>)">
            <div class="thumbnail-banner">
                <div class="logo-holder">
                    <?php
				        $logoTitle = 'Learn about ' . $data->InstitutionName;
			            print eddy_build_institution_logo($data, eddy_listing_convert_logo_size($list_fields), array('link' => $RequestInfoLink, 'linkTitle' => $logoTitle));
                    ?>
                </div>
            </div>
            <div class="caption clearfix">


                <?php if($list_fields->show_degree_info_button || $list_fields->show_school_info_button || $list_fields->show_request_info_button): ?>
                <div class="button-section clearfix">

                    <?php if($data->PaidStatusTypeId == 3 && $data->ProgramSFProductCode == 1):
                            $trackingAttributes = array(
                         'data-program-product-id' => (isset($allDetails->programDetails->ProgramProductIdClick)) ? $allDetails->programDetails->ProgramProductIdClick : 0,
                         'data-program-id' => $allDetails->programDetails->ProgramId,
                         'data-position' => 0,
                         'data-listing-type-id' => 1,
                         'data-page' => 1,
                         'data-track-clicks' => true,
                     );

                    $data->ClickTrackingAttributes = $trackingAttributes;
                    $data->ShowClickThroughLink = FALSE;
                    if(isset($data->ProgramProductIdClick) && !empty($data->ProgramProductIdClick)){

                        $data->ShowClickThroughLink = TRUE;

                    }

                    ?>

                    <div class="button-link visit-site col-md-6 col-sm-6">'.eddy_listing_visit_link("Visit Site", $details->programDetails).'</div>
                    <?php endif; ?>
                    <?php if ($list_fields->show_degree_info_button): ?>
                    <div class="button-link trending-learn-more col-md-6 col-sm-6">
                        <a title="<?php  print $ProgramLinkTitle ?>" class="button-program-info" href="<?php  print $ProgramLink ?>">
                            Learn More
                        </a>
                    </div>
                    <?php endif; ?>
                </div>
                <?php endif; ?>
              
                <?php if ($list_fields->show_program_title): ?>
                <div class="clearfix">
                    <h3>
                        <a title="<?php  print $ProgramLinkTitle ?>" href="<?php  print $ProgramLink ?>">
                            <?php print $data->ProgramName; ?>
                        </a>
                    </h3>
                </div>
                <?php endif; ?>
            </div>
        </div>
    </div>
    <?php endforeach; ?>
    <?php if($list_fields->show_pager && ($list_fields->show_pager_location == 'both' || $list_fields->show_pager_location == 'bottom')): ?>
    <div class="pager-container">
        <?php print $pager;?>
    </div>
    <?php endif;?>
</div>


