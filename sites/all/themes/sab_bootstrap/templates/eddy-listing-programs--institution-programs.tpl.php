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

<?php
$school_name = '';
if(!empty($matching_list)) {
    $school_name = $matching_list[0]->InstitutionName;
}
?>

<div id="sab-school-program-items-id" class="sab-school-program-items clearfix">


    <div class="sab-school-detail-program-head">
        Programs from <?php print $school_name;?>
        </div>
    <div itemscope itemtype="http://schema.org/EducationalOrganization">
        <div class="eddy-program-listings-container " itemscope itemprop="owns" itemtype="http://schema.org/Product">
            <ul class="eddy-listings eddy-program-listings <?php print $list_fields->machine_name ?> list-unstyled">

                <?php foreach ($matching_list as $index => $data): ?>

                <?php IF ($index % 2 == 0 ): ?>

                <div class="sab-program-item-holder clearfix">
                    <?php endif; ?>
                    <li class="<?php print $data->classes; ?> sab-school-program-item col-xs-6 <?php print ($index % 2 ? 'even' : 'odd'); ?>">
                        <div class="sab-school-program-details content-item-holder">
                            <?php if ($list_fields->show_school_title): ?>
                            <div class="sab-school-title">
                                <?php print $data->InstitutionName; ?>
                            </div>
                            <?php endif; ?>
                            <div class="programdata clearfix">
                                <?php if ($list_fields->show_program_title): ?>
                                <div class="sab-school-program-title col-xs-9" itemprop="name">
                                    <?php print eddy_listing_details_link($data->ProgramName, $data); ?>
                                </div>
                                <?php endif; ?>
                                <div class="avg-rating col-xs-3">
                                    <?php print get_avg_rating_html($data->ProgramId);?>
                                </div>
                                <?php if ($list_fields->show_program_description): ?>
                                <span class="sab-schoolprogram-desc col-xs-9">
                                    <?php print $data->ProgramShortDescription; ?>
                                </span>
                                <?php endif; ?>
                                <div class="learn-more button-link col-xs-3">

                                    <a href="/<?php print template_get_program_detail_link($data); ?>">LEARN MORE</a>
                                </div>
                            </div>
                        </div>
                    </li>
                    <?php IF ($index % 2 ): ?>
                </div>
                <?php endif; ?>
                <?php endforeach; ?>
            </ul>
        </div>
    </div>
</div>
<?php if($list_fields->show_pager && ($list_fields->show_pager_location == 'both' || $list_fields->show_pager_location == 'bottom')): ?>
<div class="pager-container">
    <?php print $pager;?>
</div>
<?php endif;?>




