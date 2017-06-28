<div id="review-recent">
    <ul>
        <?php foreach($reviews as $review):   ?>
        <li>
            <a href="/<?php print template_get_program_detail_link($review->associate_detail); ?>">
                <div class="review-provider-name">
                    <?php print isset($review->associate_detail->InstitutionName)?$review->associate_detail->InstitutionName:""; ?>
                </div>
                <div class="review-pname">
                    <?php print $review->associate_name; ?>
                </div>
                <div class="review-rating">
                    <?php print get_rating_html($review->rating); ?>
                </div>
            </a>
        </li>
        <?php endforeach;   ?>
    </ul>
</div>
