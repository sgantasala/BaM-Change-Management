<div id="review-detail-widget">
    <div class="row">
        <div class="col-xs-8 review-overall">
            <p>Overall Rating</p>
            <?php $review_score = get_reviews_total($previews['associate_id'])?>
            <?php if($review_score > 0):?>
            <div class="avg-rating">
                <?php print get_avg_rating_html($previews['associate_id']);?>
            </div>
            <p class="total-reviews">
                Based on <?php print get_reviews_total($previews['associate_id']);?> Reviews
            </p>
            <?php else: ?>
            <i class="no-review">Not Yet Reviewd</i>
            <p class="first-reviews">Be the First to Review this Program</p>
            <?php endif;?>
        </div>
        <div class="col-xs-4 review-write-link button-link">
            <a href="/admin/reviews/add/<?php print $previews['type'] . '/' . $previews['associate_id'];?>">Write A Review</a>
        </div>
    </div>
    <?php $count = (int)(variable_get('eddy_reviews_on_detail_count'));//from user's setting ?>
    <div class="col-xs-12">
        <?php $index = 0;      ?>
        <?php foreach($previews['reviews'] as $num=>$review):   ?>
        <?php if($num % $count == 0):?>
        <ul index="<?php print $index++;?>">
            <?php endif;?>
            <li>
                <div class="row">
                    <div class="col-xs-8 col-sm-9 review-title">
                        <?php print $review->title; ?>
                    </div>
                    <div class="col-xs-4 col-sm-3 review-rating">
                        <?php print get_rating_html($review->rating); ?>
                    </div>
                </div>
                <div class="review-created">
                    <?php print date("m/d/y",$review->created); ?>
                </div>
                <div class="review-description">
                    <?php print eddy_reviews_read_more($review->description); ?>
                </div>
                <div class="review-recommend">
                    Bottom Line:<?php print ($review->recommended)?"Yes, I would recommend this to a friend":"No, I would not recommend this to a friend"; ?>
                </div>

                <?php if(!empty($review->image_fid)): ?>
                <div class="review-image img-responsive">
                    <?php
                    $review_image = file_load($review->image_fid);
                    $review_image_src = file_stream_wrapper_get_instance_by_uri($review_image->uri)->getDirectoryPath() . substr($review_image->uri, strpos($review_image->uri, '://')+2);
                    ?>
                    <img src="/<?php print $review_image_src;?>" />
                </div>
                <?php endif; ?>

            </li>
            <?php if($num % $count == 4):?>
            <li class="reviews-load-more">
                <div class="button-link">
                    <a href="#">Load More Reviews</a>
                </div>
            </li>
        </ul>
        <?php endif; ?>
        <?php endforeach;   ?>
    </div>
</div>
