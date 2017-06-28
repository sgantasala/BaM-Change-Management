<?php
/**
 * Override or insert variables into the page template for HTML output.
 */
function sab_bootstrap_preprocess_html(&$vars) {
    
    $variables['classes_array'][] = 'responsive';

    drupal_add_css(drupal_get_path('theme', 'sab_bootstrap') . '/js/meanmenu/meanmenu.css');
    drupal_add_js(drupal_get_path('theme', 'sab_bootstrap') .'/js/meanmenu/jquery.meanmenu.min.js');
    
    //add product-list-page class to product_list and product list node page
    if(function_exists('sab_product_list_show_block') && sab_product_list_show_block()){
        $vars['classes_array'][] = 'product-list-page';
    }

    //add class to body when it's a article_categories vocabulary taxonomy term page
    if(arg(0) == 'taxonomy' && arg(1) == 'term' && is_numeric(arg(2))){

        $term = taxonomy_term_load(arg(2));        
        if($term->vocabulary_machine_name == "article_categories"){
            $vars['classes_array'][] = 'article-categories-vocabulary';
        }
    }
}
/**
 * Override or insert variables into the page template.
 */
function sab_bootstrap_preprocess_page(&$variables){
 
    $page = $variables['page'];

    $side_bar_column = "col-sm-3";
    $content_column_class = "col-sm-12";
        
    if(!drupal_is_front_page()){

        if($page['sidebar_first']){
            $content_column_class = "col-sm-9";
        }
            
    }
        
    $variables['side_bar_column'] = $side_bar_column;
    $variables['content_column_class'] = $content_column_class;   
    
    //institution detail and program detail page
    if(is_program_details_page() || (isset($variables['node']) && $variables['node']->type == 'institution')){
        drupal_add_js(
            array(
            'hide_content_by_words' => theme_get_setting('mobile_hide_program_content_over_char'),
            ),
        'setting');
    }

    //student guide
    if(isset($variables['node']) && $variables['node']->type == "student_guide"){
        $variables['title'] = 'Student Guide';
    }
   
    //program type aggregator not display title    
    if(isset($variables['node']) && $variables['node']->type == "general_purpose_page" && strpos(strtolower($variables['node']->title),"program type") !== false){
        $variables['title'] = '';
    }

    //blank slate page
    if(isset($variables['node'])){

        if($variables['node']->type == "blank_slate_page")
                
            $variables['theme_hook_suggestions'][]='page__node__blank_slate_page';

    }else
    {
        switch(arg(2))
        {
            case 'edit-field-drag-and-drop':
            case 'edit-css':
                $variables['theme_hook_suggestions'][]='page__node__blank_slate_page';
                break;
        }
        
    }

    //add header-banner for landing-page
    if(arg(0) == 'landing-page'){
        $attrs = $variables['page']['header_banner'];
        $qs = array_change_key_case(drupal_get_query_parameters(), CASE_LOWER);       
        
        $lp_header = variable_get('lp_header');
        if(!empty($lp_header)){
            if(array_key_exists('country', $qs)){
                $lp_header .= ' in ';
                if(array_key_exists('city', $qs) && array_key_exists('country', $qs))
                    $lp_header .= '<span id="city"></span>, ';
                
                $lp_header .= '<span id="country"></span>';
                
            }
            $lp_header .= '!';
        }
        $lp_testimonials = array();
        $lp_testimonials = explode(";@", variable_get('lp_testimonials'));
        
        foreach($attrs as $k=>$attr){
            if(is_array($attr) && array_key_exists('#block',$attr)){
                
                if(strpos($variables['page']['header_banner'][$k]['#markup'],'lp-header')){
                    $variables['page']['header_banner'][$k]['#markup'] = "<div id=\"lp-header\">$lp_header</div>";
                    if(!empty($lp_testimonials)){
                        $variables['page']['header_banner'][$k]['#markup'] .= "<div id=\"lp-testimonials\">";
                        foreach($lp_testimonials as $lk=>$lp_testimonial){
                            $variables['page']['header_banner'][$k]['#markup'] .= "<div class=\"lp-testimonial\" id=\"t$lk\"><i class=\"fa fa-quote-left\"></i>$lp_testimonial<i class=\"fa fa-quote-right\"></i></div>";
                        }
                        $variables['page']['header_banner'][$k]['#markup'] .= "</div>";
                    }
                }
            }
        }
    }
    
}

/**
 * Override or insert variables into the node template.
 */
function sab_bootstrap_preprocess_node(&$vars) {

    if(node_is_page($vars['node'])){        
        
        if(!empty($vars['content']['body'][0]['#markup']) && preg_match('/<!--break-->/', $vars['content']['body'][0]['#markup'])){
            
            $title = "";
                        
            $vars['classes_array'][] = 'hide-show-summary';
            
            $content = $vars['content']['body'][0]['#markup'];
            
            $vars['content']['body'][0]['#markup'] = "<div class=\"clearfix\">";
            $vars['content']['body'][0]['#markup'] .= preg_replace('/<!--break-->/', '<div id="summary-body-hidden" class="clearfix cleared" style="display:none;">', $title . '<div class="field-body-content">' . $content . '</div>');
            $vars['content']['body'][0]['#markup'] .= "</div>";
            $vars['content']['body'][0]['#markup'] .= "</div>";
            
            $read_more_content = explode('<!--break-->', $content);
            
            if(isset($read_more_content[1]) && !empty($read_more_content[1])){
                $vars['content']['body'][0]['#markup'] .= "<div id=\"summary-read-more\"><a href=\"#\">Read More</a></div>";
            }
            
        }


        //hide product list page body content if has allowed query string
        $qs = array_change_key_case(drupal_get_query_parameters(), CASE_LOWER);
        if(!empty($qs)){            
            foreach($qs as $k=>$v){
                if(in_array($k, array('in', 'duration', 'work_type', 'level', 'term'))){
                    
                    if(isset($vars['content']['body'])){
                        unset($vars['content']['body']);
                        break;
                    }
                    
                }
            }
        }
        
    }
}

/**
 * Override or insert variables into the block template.
 */
function sab_bootstrap_preprocess_block(&$variables){

    // Add arbitrary class to specific block
    if (($variables['block']->module == 'sab_program_details' || $variables['block']->module == 'eddy_reviews') && is_program_details_page()) {
        $current_details = get_sab_program_details();
        $variables['classes_array'][] = ($current_details->programDetails->PaidStatusTypeId == '1')?"free":"";
    }
}

function sab_bootstrap_menu_tree(&$variables){
    
    if($variables['theme_hook_original'] == 'menu_tree__menu_program_type'){
        return '<div class="menu-container"><ul class="menu">' . $variables['tree'] . '</ul></div>';
    }else{
        return '<ul class="menu">' . $variables['tree'] . '</ul>';
    }
}

function sab_bootstrap_preprocess_menu_tree(&$variables){

    //add '</ul><ul>' after 3rd li to make two ul.
    //this is for two rows program type 
    if($variables['theme_hook_original'] == 'menu_tree__menu_program_type'){
        $menu_new_html = "";
        $menu_html = $variables['tree'];

        $menu_tree = explode("<li", $menu_html);
        if(count($menu_tree) > 1){
            unset($menu_tree[0]);
            foreach($menu_tree as $k=>$menu){
                if($k == '3'){
                    $menu.= "</ul><ul class=\"menu second\">";
                }
                $menu_new_html.="<li" . $menu;
            }
            $variables['tree'] = $menu_new_html;
        }
    }
}


/**
 * Overrides theme_menu_link().
 * Have to alter the menu links again. Want to make this configurable.
 */
function sab_bootstrap_menu_link(array $variables) {
    
    $element = $variables['element'];
    $sub_menu = '';
    //dpm($element);

    if ($element['#below']) {
        // Prevent dropdown functions from being added to management menu so it
        // does not affect the navbar module.
        if (($element['#original_link']['menu_name'] == 'management') && (module_exists('navbar'))) {
            $sub_menu = drupal_render($element['#below']);
        }
        elseif ((!empty($element['#original_link']['depth'])) && ($element['#original_link']['depth'] == 1)) {
            // Add our own wrapper.
            unset($element['#below']['#theme_wrappers']);
            $sub_menu = '<ul class="dropdown-menu">' . drupal_render($element['#below']) . '</ul>';
            // Generate as standard dropdown.
            $element['#title'] .= ' <span class="caret"></span>';
            $element['#attributes']['class'][] = 'dropdown';
            $element['#localized_options']['html'] = TRUE;

            // Set dropdown trigger element to # to prevent inadvertant page loading
            // when a submenu link is clicked.
            $element['#localized_options']['attributes']['data-target'] = '#';
            $element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';

            //article-blog menu remove data-toggle to make parent menu link to work
            if($element['#original_link']['menu_name'] != 'menu-article-blog-menu'){
                $element['#localized_options']['attributes']['data-toggle'] = 'dropdown';
            }
        }
    }
    // On primary navigation menu, class 'active' is not set on active menu item.
    // @see https://drupal.org/node/1896674
    if (($element['#href'] == $_GET['q'] || ($element['#href'] == '<front>' && drupal_is_front_page())) && (empty($element['#localized_options']['language']))) {
        $element['#attributes']['class'][] = 'active';
    }

    if($element['#href'] == "<none>"){
        $element['#href'] = "#";
        $element['#localized_options']['fragment'] = "";
        $element['#localized_options']['external'] = TRUE;
    }
    
    $output = l($element['#title'], $element['#href'], $element['#localized_options']);
    return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";

}

function sab_bootstrap_form_alter(&$form, $form_state, $form_id){
    
    //Prevent Newsletter from redirecting to the node page if it is a block and if there is no redirect URL.
    if(
        (isset($form['#node']) && !node_is_page($form['#node'])) && 
        (isset($form['#node']->webform['redirect_url']) && $form['#node']->webform['redirect_url'] == '<none>')
      ){
        $form['#action'] = "";
    }
    
    if(isset($form['#node']) && $form['#node']->type == 'webform'){

        $form['#validate'][] = 'sab_webform_validate_common_fields';
    }
  
    if($form_id == 'webform_client_form_13739'){
    
        $form['submitted']['FirstName']['#attributes']['placeholder'] = 'First Name';
        
        $form['submitted']['LastName']['#attributes']['placeholder'] = 'Last Name';
        
        $form['submitted']['Email']['#attributes']['placeholder'] = 'Email Address';
        

    }
}

/**
 * Additional Validation for Certian Webform fields.
 */
function sab_webform_validate_common_fields(&$form, $form_state){
    
    if(isset($form_state['input']['submitted'])){
        
        $form_values = $form_state['input']['submitted'];
        $email = "";
        if(isset($form_values['email_address'])){
            
            $email = $form_values['email_address'];
            
        }
        
        if(!empty($email)){
            
            $url = variable_get("eddy_forms_engine_service_domain") . "/FormValidation/EmailCheck/?EmailVerificationLevel=3&EmailAddress=" . urlencode($email) . "&callback=c";
            
            $result = drupal_http_request($url);
            
            if(strpos($result->data, 'false')){
                
                form_set_error('email_address', "Please enter a valid Email Address.");
                
            }

        }
        
        //$phone = "";
        //if(isset($form_values['phone_number'])){
            
        //    $phone = $form_values['phone_number'];
            
        //}else if(isset($form_values['PhoneNumber'])){
            
        //    $phone = $form_values['PhoneNumber'];
            
        //}
        
        //if(!empty($phone)){
            
        //    $url = variable_get("eddy_forms_engine_service_domain") . "/FormValidation/PhoneNumberCheck/?CountryCode=US&PhoneNumber=$phone&callback=c";
            
        //    $result = drupal_http_request($url);
            
        //    if(strpos($result->data, 'false')){

        //        form_set_error('phone_number', "Please enter a valid Phone Number");
                
        //    }
            
        //}
        
    }

}


/**
 * Implements hook_css_alter()
 */
function sab_bootstrap_css_alter(&$css){

    foreach($css as $k=>$c){
        //set dynamic customized css file to higher priority
        if(is_array($css[$k]['data']) || (is_string($css[$k]['data']) && preg_match('/eddy-css-to-file/', $css[$k]['data']))){
            $css[$k]['group'] = 200;
        }
        if(module_exists('eddy_css_to_file')){
            //unset inline customized css
            if($c['type'] == 'inline'){
                unset($css[$k]);
            }
        }
    }
}
function show_artical_blog_menu(){
    
    //display menu on blogger user page
    if(arg(0) == 'user' && is_numeric(arg(1))){
        $user = user_load(arg(1));
        if(!empty($user->roles)){
            foreach($user->roles as $role){
                if(strtolower($role) == "blogger"){
                    return true;
                }
            }
        }
        
    }
    //display menu on blog or article page
    elseif(arg(0) == 'node' && is_numeric(arg(1))){
        $node = node_load(arg(1));
        if($node->type == 'blogs_post' || $node->type == 'article_page' || $node->type == 'student_guide'){
            return true;
        }
    }
    //display menu on blog or article aggregator page
    elseif(arg(0) == 'blogs' || arg(0) == 'resources'){
        return true;
    }
    //display menu on "article_categories" taxonomy vacabulary page
    elseif(arg(0) == 'taxonomy' && arg(1) == 'term' && is_numeric(arg(2))){

        $term = taxonomy_term_load(arg(2));        
        if($term->vocabulary_machine_name == "article_categories"){
            return true;
        }
    }
    
    return false;
}

/** 
 * Custom function 
 **/
//function text_accordion($html,$length){
//    //dpm($string);
//    $accordion = array();
    
//    if (strlen($html) > $length){

//        $text = substr($html, 0, $length);

//        $remaining = explode(' ', substr($html, $length));
        
//        $accordion['main'] = $text;
//        $accordion['remain'] = $remaining;
//        //$text .= $remaining[0];
//        //$text .= (count($remaining)>1)?'&nbsp;<a href="#" class="review-read-more">' . variable_get('eddy_reviews_read_more_text') . '</a>':'';
        
//        return $html;

//    }else{
//        $accordion['main'] = $html;
//        return $html;
//    }
//}

function template_get_program_detail_link($detail){
    
    if(module_exists('sab_program_details') && function_exists('sab_program_details_create_url') && !empty($detail)){
        return sab_program_details_create_url("institutions", $detail);
    }else{
        return "";
    }
}

function template_is_program_details_page(){
    if(module_exists('sab_program_details') && function_exists('is_program_details_page')){
        return is_program_details_page();
    }else{
        return "";
    }
}

function template_get_avg_rating_html($id){
    if(module_exists('eddy_reviews') && function_exists('get_rating_html')){
        return get_rating_html($id);
    }else{
        return "";
    }
}

function template_sab_listing_institution_details_link($link_text, $detail, $link_options = array()){
    if(module_exists('sab_listing') && function_exists('sab_listing_institution_details_link')){
        return sab_listing_institution_details_link($link_text, $detail, $link_options);
    }else{
        return "";
    }
}