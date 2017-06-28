<div id="review-recent">
    <ul>
    <?php foreach($reviews as $review):   ?>
        <li>
            <a href="#">
                <div class="review-provider-name"><?php print $review->associate_detail->InstitutionName; ?></div>
                <div class="review-pname"><?php print $review->associate_name; ?></div>
                <div class="review-rating"><?php print get_rating_html($review->rating); ?></div>
            </a>
        </li>
    <?php endforeach;   ?>
    </ul>
</div>