<?php

function _sab_oas_ads_format_as_machine_readable_string($human_readable_string)
{
    $machine_readable_string = strtolower($human_readable_string);
    $machine_readable_string = preg_replace('@[^a-z0-9_]+@','_',$machine_readable_string);
    return $machine_readable_string;
}


function sab_oas_ads_render_ad($position_id)
{
	$markup = '';
	try
	{
        $position = sab_oas_ads_get_position_by_position_id($position_id);
        //dpm($position);
        switch ($position->oas_position_id)
		{


            case 'x11':
                $markup = '';
                break;
            case 'Position1':
            case 'Bottom1':
            case 'Bottom2':
            case 'Bottom3':
                $markup = sab_oas_ads_ad_markup($position);
                break;

            default:
                $markup = sab_oas_ads_ad_markup($position);
                break;
		}
	}

	catch(Exception $e)
	{
		watchdog_exception('sab_oas_ads', $e);
	}

	return $markup;
}

function sab_oas_ads_ad_markup($position)
{
	$markup = '';
	try
	{
        $classes = 'hidden-xs hidden-sm';
        if($position->is_mobile_position)
        {
            $classes = 'hidden-md hidden-lg text-center';
        }
		$markup.= '<div id="OAS_' . $position->oas_position_id . '" class="'.$classes.'">';
        $markup.= '<script type="text/javascript">';
        //$markup.= '(function ($) {';
        //$markup.= '$(document).ready(function () {';
        $markup.= 'OAS_AD(\'' . $position->oas_position_id . '\');';
        //$markup.= '});';
        //$markup.= '})(jQuery);';
        $markup.= '</script>';
        $markup.= '</div>';
		$markup.= "\r";
		$markup.= '<div id="Hidden_OAS_' . $position->oas_position_id . '" style="display: none;"></div>';
		$markup.= "\r";
	}

	catch(Exception $e)
	{
		watchdog_exception('sab_oas_ads', $e);
	}

	return $markup;
}

function sab_oas_ads_slide_up_ad_markup($position)
{

	$markup = '';
	try
	{
        //drupal_add_js(drupal_get_path('module', 'sab_oas_ads') . '/js/sab_oas_slide_up_ad.js', array('every_page' => true));
        //$markup.= '<div id="SlideUpContainer" style="display:none;">';

        //$markup.= '<div id="SlideUpInner">';

        //$markup.= '<table  border="0" align="center" cellpadding="0" cellspacing="0">';

        //$markup.= '<tr>';

        //$markup.= ' <th align="right" valign="bottom" scope="col">';
        //$markup.= '<span id="closeAdvertMobile">';

        //$markup.= 'X Close';

        //$markup.= '</span>';
        //$markup.= '<div id="OAS_' . $position->oas_position_id . '" class="hidden-xs hidden-sm" ><script type="text/javascript">OAS_AD(\'' . $position->oas_position_id . '\');</script></div>';

        //$markup.= '<div id="Hidden_OAS_' . $position->oas_position_id . '" style="display: none;"></div>';
        //$markup.= '<div id="OAS_x22" class="hidden-md hidden-lg"><script type="text/javascript">OAS_AD("x22");</script></div>';

        //$markup.= '<div id="Hidden_OAS_x22" style="display: none;"></div>';
        //$markup.= '</th>';

        //$markup.= '<th scope="col">';

        //$markup.= '<span id="closeAdvert">';

        //$markup.= '<img src="'.base_path().drupal_get_path('module', 'sab_oas_ads').'/images/slide_up_close_button.png" width="27" height="34" border="0" id="BannerClose" />';

        //$markup.= '</span><br />';

        //$markup.= '</th>';

        //$markup.= '</tr>';

        //$markup.= '</table>';

        //$markup.= '</div>';

        //$markup.= '</div>';




	}

	catch(Exception $e)
	{
		watchdog_exception('sab_oas_ads', $e);
	}

	return $markup;
}

function sab_oas_ads_set_multiple_position_script($positions)
{
	try
	{

        $site_page_string = sab_oas_ads_get_site_page_string();
        drupal_add_js(array('sab_oas_ads' => array('current_site_page' =>  $site_page_string)),'setting');
		drupal_add_css(drupal_get_path('module', 'sab_oas_ads') . '/style/sab_oas_ads_style.css', array(
			'group' => CSS_DEFAULT,
			'every_page' => TRUE
		));
		$script = "\r";
		$script = 'OAS_url = "http://oascentral.educationdynamics.com/RealMedia/ads/";';
		$script.= "\r";
		$script.= 'OAS_sitepage ="' . sab_oas_ads_get_site_page_string() . '";';
		$script.= "\r";
		$script.= 'OAS_listpos = "' . $positions . '";';
		$script.= "\r";
		$script.= 'OAS_query = "";';
		$script.= "\r";
		$script.= 'OAS_target = "_top";';
		$script.= "\r";
		$script.= 'OAS_version = 11;';
		$script.= "\r";
		$script.= 'OAS_rn = "001234567890";';
		$script.= "\r";
		$script.= 'OAS_rns = "1234567890";';
		$script.= "\r";
		$script.= 'OAS_rn = new String(Math.random());';
		$script.= "\r";
		$script.= 'OAS_rns = OAS_rn.substring(2, 11);';
		$script.= 'function OAS_NORMAL(pos) {';
		$script.= "\r";
		$script.= 'document.write(\'<A rel="nofollow" HREF="\' + OAS_url + \'click_nx.ads/\' + OAS_sitepage + \'/1\' + OAS_rns + \'@\' + OAS_listpos + \'!\' + pos + \'?\' + OAS_query + \'TARGET=\' + OAS_target + \'>\');';
		$script.= "\r";
		$script.= 'document.write(\'<IMG SRC="\' + OAS_url + \'adstream_nx.ads/\' + OAS_sitepage + \'/1\' + OAS_rns + \'@\' + OAS_listpos + \'!\' + pos + \'?\' + OAS_query + \'" BORDER=0></A>\');';
		$script.= "\r";
		$script.= '}';
		$script.= "\r";
		$script.= 'function getObj(name) {';
		$script.= "\r";
		$script.= 'if (document.getElementById) this.obj = document.getElementById(name);';
		$script.= "\r";
		$script.= '    else if (document.all) this.obj = document.all[name];';
		$script.= "\r";
		$script.= '    else if (document.layers) this.obj = document.layers[name];';
		$script.= "\r";
		$script.= 'if (this.obj) this.style = this.obj.style;';
		$script.= "\r";
		$script.= '}';
		$script.= "\r";
		$script.= 'function addLoad(func) {';
		$script.= "\r";
		$script.= ' if (window.addEventListener) window.addEventListener("load", func, false);';
		$script.= "\r";
		$script.= ' else if (document.addEventListener) document.addEventListener("load", func, false);';
		$script.= "\r";
		$script.= ' else if (window.attachEvent) window.attachEvent("onload", func);';
		$script.= "\r";
		$script.= ' else if (typeof window.onload != "function") window.onload = func;';
		$script.= "\r";
		$script.= ' else {';
		$script.= "\r";
		$script.= '     var oldonload = window.onload;';
		$script.= "\r";
		$script.= '     window.onload = function() {';
		$script.= "\r";
		$script.= '     oldonload();';
		$script.= "\r";
		$script.= '     func();';
		$script.= "\r";
		$script.= ' };';
		$script.= "\r";
		$script.= '}';
		$script.= "\r";
		$script.= '}';
		$script.= "\r";
		$script.= 'function OAS_AMJX_init() {';
		$script.= "\r";
		$script.= 'var apos = OAS_listpos.split(\',\');';
		$script.= "\r";
		$script.= 'var olddocwrite = document.write;';
		$script.= "\r";
		$script.= 'for (var i = 0; i < apos.length; i++) {';
		$script.= "\r";
		$script.= 'var object_togo = new getObj(\'OAS_\' + apos[i]);';
		$script.= "\r";
		$script.= 'var object_tomove = new getObj(\'Hidden_OAS_\' + apos[i]);';
		$script.= "\r";
		$script.= 'html = \'\';';
		$script.= "\r";
		$script.= 'if (object_togo.obj != null && object_tomove.obj != null) {';
		$script.= "\r";
		$script.= 'if (typeof (object_togo.obj) != "undefined" && typeof (object_tomove.obj) != "undefined") {';
		$script.= "\r";
		$script.= 'object_togo.obj.appendChild(object_tomove.obj);';
		$script.= "\r";
		$script.= 'object_tomove.style.display = "inline";';
		$script.= "\r";
		$script.= '}';
		$script.= "\r";
		$script.= '}';
		$script.= "\r";
		$script.= '}';
		$script.= "\r";
		$script.= '}';
		$script.= "\r";
		$script.= 'if (navigator.userAgent.indexOf(\'Mozilla/3\') != -1 || navigator.userAgent.indexOf(\'Mozilla/4.0 WebTV\') != -1) OAS_version = 10;';
		$script.= "\r";
		$script.= 'if (OAS_version >= 11) document.write(\'<script language="javascript" type="text/javascript" SRC="\' + OAS_url + \'adstream_mjx.ads/\' + OAS_sitepage + \'/1\' + OAS_rns + \'@\' + OAS_listpos + \'?\' + OAS_query + \'">\' + \'</\' + \'script>\');';
		$script.= "\r";
		$script.= 'if (document.getElementById && document.createTextNode)';
		$script.= "\r";
		$script.= 'addLoad(OAS_AMJX_init);';
		$script.= "\r";
        $script .= 'var loadedAds=[];';
        $script.= "\r";
		$script.= 'function OAS_AD(pos) {';
		$script.= "\r";
        $script .= 'if(jQuery.inArray(pos,loadedAds) == -1){';
        $script.= "\r";
		$script.= 'OAS_version >= 11 ? OAS_RICH(pos) : OAS_NORMAL(pos);';
        $script.= "\r";
        $script .= 'loadedAds.push(pos);';
        $script.= "\r";
        $script .= '}';
		$script.= "\r";
		$script.= '}';
		$script.= "\r";


		$e = array(
			"#tag" => "script",
			"#attributes" => array(
				"type" => "text/javascript",
			) ,
			"#value" => $script,
		);
		drupal_add_html_head($e, 'OAS');


	}

	catch(Exception $e)
	{
		watchdog_exception('sab_oas_ads', $e);
	}
}

/**
 * Menu Callback to Load Midway Banner in Listing.
 */
function _sab_oas_get_midway_ad()
{

    if(isset($_GET['site_page']) && isset($_GET['pos'])){

        $page = $_GET['site_page'];
        $pos = $_GET['pos'];
	    $script = "\r";
	    $script = 'OAS_url = "http://oascentral.educationdynamics.com/RealMedia/ads/";';
	    $script.= "\r";
	    $script.= 'OAS_sitepage ="' . $page . '";';
	    $script.= "\r";
	    $script.= 'OAS_listpos = "'.$pos.'";';
	    $script.= "\r";
	    $script.= 'OAS_query = "";';
	    $script.= "\r";
	    $script.= 'OAS_target = "_top";';
	    $script.= "\r";
	    $script.= 'OAS_version = 11;';
	    $script.= "\r";
	    $script.= 'OAS_rn = "001234567890";';
	    $script.= "\r";
	    $script.= 'OAS_rns = "1234567890";';
	    $script.= "\r";
	    $script.= 'OAS_rn = new String(Math.random());';
	    $script.= "\r";
	    $script.= 'OAS_rns = OAS_rn.substring(2, 11);';
	    $script.= 'function OAS_NORMAL(pos) {';
	    $script.= "\r";
	    $script.= 'document.write(\'<A rel="nofollow" HREF="\' + OAS_url + \'click_nx.ads/\' + OAS_sitepage + \'/1\' + OAS_rns + \'@\' + OAS_listpos + \'!\' + pos + \'?\' + OAS_query + \'TARGET=\' + OAS_target + \'>\');';
	    $script.= "\r";
	    $script.= 'document.write(\'<IMG SRC="\' + OAS_url + \'adstream_nx.ads/\' + OAS_sitepage + \'/1\' + OAS_rns + \'@\' + OAS_listpos + \'!\' + pos + \'?\' + OAS_query + \'" BORDER=0></A>\');';
	    $script.= "\r";
	    $script.= '}';
	    $script.= "\r";
	    $script.= 'function getObj(name) {';
	    $script.= "\r";
	    $script.= 'if (document.getElementById) this.obj = document.getElementById(name);';
	    $script.= "\r";
	    $script.= '    else if (document.all) this.obj = document.all[name];';
	    $script.= "\r";
	    $script.= '    else if (document.layers) this.obj = document.layers[name];';
	    $script.= "\r";
	    $script.= 'if (this.obj) this.style = this.obj.style;';
	    $script.= "\r";
	    $script.= '}';
	    $script.= "\r";
	    $script.= 'function addLoad(func) {';
	    $script.= "\r";
	    $script.= ' if (window.addEventListener) window.addEventListener("load", func, false);';
	    $script.= "\r";
	    $script.= ' else if (document.addEventListener) document.addEventListener("load", func, false);';
	    $script.= "\r";
	    $script.= ' else if (window.attachEvent) window.attachEvent("onload", func);';
	    $script.= "\r";
	    $script.= ' else if (typeof window.onload != "function") window.onload = func;';
	    $script.= "\r";
	    $script.= ' else {';
	    $script.= "\r";
	    $script.= '     var oldonload = window.onload;';
	    $script.= "\r";
	    $script.= '     window.onload = function() {';
	    $script.= "\r";
	    $script.= '     oldonload();';
	    $script.= "\r";
	    $script.= '     func();';
	    $script.= "\r";
	    $script.= ' };';
	    $script.= "\r";
	    $script.= '}';
	    $script.= "\r";
	    $script.= '}';
	    $script.= "\r";
	    $script.= 'function OAS_AMJX_init() {';
	    $script.= "\r";
	    $script.= 'var apos = OAS_listpos.split(\',\');';
	    $script.= "\r";
	    $script.= 'var olddocwrite = document.write;';
	    $script.= "\r";
	    $script.= 'for (var i = 0; i < apos.length; i++) {';
	    $script.= "\r";
	    $script.= 'var object_togo = new getObj(\'OAS_\' + apos[i]);';
	    $script.= "\r";
	    $script.= 'var object_tomove = new getObj(\'Hidden_OAS_\' + apos[i]);';
	    $script.= "\r";
	    $script.= 'html = \'\';';
	    $script.= "\r";
	    $script.= 'if (object_togo.obj != null && object_tomove.obj != null) {';
	    $script.= "\r";
	    $script.= 'if (typeof (object_togo.obj) != "undefined" && typeof (object_tomove.obj) != "undefined") {';
	    $script.= "\r";
	    $script.= 'object_togo.obj.appendChild(object_tomove.obj);';
	    $script.= "\r";
	    $script.= 'object_tomove.style.display = "inline";';
	    $script.= "\r";
	    $script.= '}';
	    $script.= "\r";
	    $script.= '}';
	    $script.= "\r";
	    $script.= '}';
	    $script.= "\r";
	    $script.= '}';
	    $script.= "\r";
	    $script.= 'if (navigator.userAgent.indexOf(\'Mozilla/3\') != -1 || navigator.userAgent.indexOf(\'Mozilla/4.0 WebTV\') != -1) OAS_version = 10;';
	    $script.= "\r";
	    $script.= 'if (OAS_version >= 11) document.write(\'<script language="javascript" type="text/javascript" SRC="\' + OAS_url + \'adstream_mjx.ads/\' + OAS_sitepage + \'/1\' + OAS_rns + \'@\' + OAS_listpos + \'?\' + OAS_query + \'">\' + \'</\' + \'script>\');';
	    $script.= "\r";
	    $script.= 'if (document.getElementById && document.createTextNode)';
	    $script.= "\r";
	    $script.= 'addLoad(OAS_AMJX_init);';
	    $script.= "\r";
	    $script.= 'function OAS_AD(pos) {';
	    $script.= "\r";
	    $script.= 'OAS_version >= 11 ? OAS_RICH(pos) : OAS_NORMAL(pos);';
	    $script.= "\r";
	    $script.= '}';
	    $script.= "\r";
	    $e = array(
		    "#tag" => "script",
		    "#attributes" => array(
			    "type" => "text/javascript",
		    ) ,
		    "#value" => $script,
	    );

        $gtmScript= "(function(w,d,s,l,i){w[l]=w[l]||[];w[l].push({'gtm.start':new Date().getTime(),event:'gtm.js'});var f=d.getElementsByTagName(s)[0];var j=d.createElement(s);var dl=l!='dataLayer'?'&l='+l:'';j.src='//www.googletagmanager.com/gtm.js?id='+i+dl;j.type='text/javascript';j.async=true;f.parentNode.insertBefore(j,f);})(window,document,'script','dataLayer','GTM-K8ZHHR');";
        $gtmScriptArray = array(
		    "#tag" => "script",
		    "#attributes" => array(
			    "type" => "text/javascript",
		    ) ,
		    "#value" => $gtmScript,
	    );

        $oas_ad_script ='/'.drupal_get_path('module', 'sab_oas_ads') . '/js/sab_oas_ads_script.js';
        print "<html><body><script =\"text/javascript\">$script</script><script =\"text/javascript\">$gtmScript</script>";

        print '<div id="oas-add-holder">
                <div id="OAS_'.$pos.'">
                    <script type="text/javascript">OAS_AD("'.$pos.'");</script>
                </div>
                <div id="Hidden_OAS_'.$pos.'" style="display: none;"></div>
            </div></body>
            <script =\"text/javascript\">
            document.getElementById(\'OAS_'.$pos.'\').onclick=function(){

                var eventCategory = \'client\';
                var eventAction = \'OAS_'.$pos.'\';
                if (typeof dataLayer != \'undefined\') {
                    dataLayer.push({
                        "event": "gaEvent",
                        "eventCategory": eventCategory,
                        "eventAction": eventAction
                    });
                }
                window[\'optimizely\'] = window[\'optimizely\'] || [];
                window.optimizely.push(["trackEvent", eventAction]);

            }
            </script>
            </html>';

        drupal_exit();

    }

}

function sab_oas_ads_position_save($position)
{
	$is_successfull = false;
	$response_message = array();
	try
	{
		if (!is_null($position))
		{
			if (isset($position['id']))
			{
				if (is_numeric($position['id']))
				{

					if ($position['id'] == 0)
					{
						$position['created'] = REQUEST_TIME;
						$position['changed'] = REQUEST_TIME;
						unset($position['id']);
						db_insert('oas_ads_positions')->fields($position)->execute();
					}
					else
					{
						$current_id = $position['id'];
                        $original_position = sab_oas_ads_get_position_by_id($current_id);
                        if (!is_null($original_position))
                        {
                            $position['changed'] = REQUEST_TIME;
                            unset($position['id']);
                            db_update('oas_ads_positions')->fields($position)->condition('id', $current_id)->execute();
                            //manage existing blocks
                            sab_oas_ads_block_update($original_position->oas_position_id,$position['oas_position_id']);
                        }
					}

					$is_successfull = true;
				}
			}
		}
	}

	catch(Exception $e)
	{
		watchdog_exception('sab_oas_ads', $e);
	}

	$response_message['success'] = $is_successfull;
	$response_message['position'] = $position;
	return $response_message;
}

function sab_oas_ads_position_delete($id)
{
	$is_successfull = false;
	try
	{
		if (is_numeric($id))
		{
            $original_position = sab_oas_ads_get_position_by_id($current_id);
            if (!is_null($original_position))
            {
                db_delete('oas_ads_positions')->condition('id', $id)->execute();
                //manage existing blocks
                sab_oas_ads_block_delete($original_position->oas_position_id);
            }

			$is_successfull = true;
		}
	}

	catch(Exception $e)
	{
		watchdog_exception('sab_oas_ads', $e);
	}

	return $is_successfull;
}

function sab_oas_ads_positions_list_paged($page_size, $arg1)
{
	$results = null;
	try
	{
		$order_by = 'created';
		$allowed = array(
			'name',
			'created',
			'updated'
		);
		$arg1 = str_replace('-', '_', $arg1);
		if (in_array($arg1, $allowed))
		{
			$order_by = $arg1;
		}

		$results = db_select('oas_ads_positions', 'e')->fields('e')->orderby($order_by, 'DESC')->extend('PagerDefault')->limit($page_size)->execute()->fetchAllAssoc('id');
	}

	catch(Exception $e)
	{
		watchdog_exception('sab_oas_ads', $e);
	}

	return $results;
}

function sab_oas_ads_positions_id_array($page_size, $order_by)
{
	$ad_postions_array = array();
	try
	{
		$results = sab_oas_ads_positions_list_paged($page_size, $order_by);

		foreach($results as $ad_postion)
		{
			$ad_postions_array[$ad_postion->oas_position_id] = $ad_postion->oas_position_id;
		}
	}

	catch(Exception $e)
	{
		watchdog_exception('sab_oas_ads', $e);
	}

	return $ad_postions_array;
}

function sab_oas_ads_get_position_by_id($id)
{
	$result = null;
	try
	{

		$result = db_select('oas_ads_positions', 'e')->fields('e')->condition('id', $id)->execute()->fetchObject();
	}

	catch(Exception $e)
	{
		watchdog_exception('sab_oas_ads', $e);
	}

	return $result;
}
function sab_oas_ads_get_position_by_position_id($position_id)
{
	$result = null;
	try
	{

		$result = db_select('oas_ads_positions', 'e')->fields('e')->condition('oas_position_id', $position_id)->execute()->fetchObject();
	}

	catch(Exception $e)
	{
		watchdog_exception('sab_oas_ads', $e);
	}

	return $result;
}
function sab_oas_ads_block_update($original_delta,$new_delta)
{

    db_update('block')
    ->fields(array('delta' => $new_delta))
   ->condition('delta', $original_delta, '=')
    ->execute();
}
function sab_oas_ads_block_delete($delta)
{
    db_delete('block')
   ->condition('module', 'sab_oas_ads', '=')
   ->condition('delta', $delta, '=')
   ->execute();

}

function sab_oas_ads_get_site_page_string()
{
	$oas_site_page ='';
	try
	{
		$site_page_string = '';
		$path = current_path();
		$path_alias = drupal_lookup_path('alias', $path);
		$arguments = explode('/', current_path());

		switch ($arguments[0])
		{
            case 'home':
                $oas_site_page = 'studyabroad/home';
                break;
            case 'resources':
                $oas_site_page = 'studyabroad/resources';
                break;
            case 'node':

                $existing_node = entity_load('node', array(
                    $arguments[1]
                ));

                if (count($existing_node) > 0)
                {
                    if (!is_null($existing_node))
                    {
                        $current_node = $existing_node[$arguments[1]];
                        if (!is_null($current_node))
                        {
                            if(property_exists($current_node, 'field_oas_sitepage_override')){
                                if (count($current_node->field_oas_sitepage_override))
                                {
                                    if(!empty($current_node->field_oas_sitepage_override[LANGUAGE_NONE][0]['value'])){
                                        $oas_site_page = $current_node->field_oas_sitepage_override[LANGUAGE_NONE][0]['value'];
                                        return $oas_site_page;
                                    }
                                }
                            }
                            if (property_exists($current_node, 'type'))
                            {
                                switch ($current_node->type)
                                {
                                    case 'error_page':
                                        $oas_site_page ='studyabroad/error404';
                                    case 'page':
                                        dpm('page');
                                        $oas_site_page ='studyabroad/';
                                    case 'aggregator_page':
                                        switch ($path_alias)
                                        {
                                            case 'institutions':
                                                $oas_site_page = 'studyabroad/zero/institution';
                                                break;

                                        }
                                        break;
                                    case 'product_list':

                                        $has_subject = false;

                                        if (property_exists($current_node, 'field_category_tr'))
                                        {
                                            if (count($current_node->field_category_tr))
                                            {
                                                $category_url_fragment = sab_oas_ads_get_term_legacy_url_fragment($current_node->field_category_tr[LANGUAGE_NONE][0]['tid']);
                                                if (!empty($category_url_fragment))
                                                {
                                                    $site_page_string.= $category_url_fragment . '/';
                                                }
                                            }
                                        }

                                        if (property_exists($current_node, 'field_subject_tr'))
                                        {
                                            if (count($current_node->field_subject_tr))
                                            {
                                                $subject_url_fragment = sab_oas_ads_get_term_legacy_url_fragment($current_node->field_subject_tr[LANGUAGE_NONE][0]['tid']);
                                                if (!empty($subject_url_fragment))
                                                {
                                                    $site_page_string.= $subject_url_fragment . '/';
                                                }

                                                $has_subject = true;
                                            }
                                        }

                                        if (property_exists($current_node, 'field_specialty_tr'))
                                        {
                                            if (count($current_node->field_specialty_tr))
                                            {
                                                $specialty_url_fragment = sab_oas_ads_get_term_legacy_url_fragment($current_node->field_specialty_tr[LANGUAGE_NONE][0]['tid']);
                                                if (!empty($specialty_url_fragment))
                                                {
                                                    $site_page_string.= $specialty_url_fragment . '/';
                                                }

                                                $has_subject = true;
                                            }
                                        }

                                        if ($has_subject)
                                        {

                                            $oas_site_page = 'studyabroad/subject/' . $site_page_string;
                                        }
                                        else
                                        {

                                            switch ($path_alias)
                                            {
                                                case 'certificate':
                                                    $oas_site_page = 'studyabroad/level/certificate';
                                                    break;
                                                case 'doctorate':
                                                    $oas_site_page = 'studyabroad/level/doctorate';
                                                    break;
                                                case 'masters':
                                                    $oas_site_page = 'studyabroad/level/masters';
                                                    break;
                                                case 'programs/online':
                                                    $oas_site_page = 'studyabroad/format/online';
                                                    break;
                                                case 'programs/on-campus':
													$oas_site_page = 'studyabroad/format/campus';
                                                    break;
												case 'programs/hybrid':
													$oas_site_page = 'studyabroad/format/hybrid';
													break;
                                                case 'programs':
                                                    if(!empty($_GET['campus_types'])){
                                                        switch ($_GET['campus_types'])
                                                        {
                                                            case 'online':
                                                                $oas_site_page = 'studyabroad/format/online';
                                                                break;
                                                            case 'campus':
                                                                $oas_site_page = 'studyabroad/format/campus';
                                                                break;
                                                            case 'hybrid':
                                                                $oas_site_page = 'studyabroad/format/hybrid';
                                                                break;
                                                        }
                                                    }
                                                    else
                                                    {
                                                        $oas_site_page = 'studyabroad/zero/subject';
                                                    }
                                                    break;
                                                default:
                                                    $oas_site_page = 'studyabroad/field/' . $site_page_string;
                                                    break;
                                            }
                                        }

                                        break;

                                    case 'article_page':
                                        $oas_site_page = 'studyabroad';
                                        break;
                                    case 'general_purpose':

                                        switch ($path_alias)
                                        {
                                            case 'home':
                                                $oas_site_page = 'studyabroad/home';
                                                break;
                                        }

                                        break;
                                    case 'regional_product_list':

                                        if (property_exists($current_node, 'field_country_tr'))
                                        {
                                            if (count($current_node->field_country_tr))
                                            {
                                                $category_url_fragment = sab_oas_ads_get_term_legacy_url_fragment($current_node->field_country_tr[LANGUAGE_NONE][0]['tid']);
                                                if (!empty($category_url_fragment))
                                                {
                                                    $site_page_string = 'country/'.$category_url_fragment . '/';

                                                }

                                            }
                                        }
                                        if (property_exists($current_node, 'field_state_tr'))
                                        {
                                            if (count($current_node->field_state_tr))
                                            {
                                                $category_url_fragment = sab_oas_ads_get_term_legacy_url_fragment($current_node->field_state_tr[LANGUAGE_NONE][0]['tid']);
                                                if (!empty($category_url_fragment))
                                                {
                                                    $site_page_string = 'state/'.$category_url_fragment . '/';

                                                }
                                            }
                                        }
                                        if (property_exists($current_node, 'field_city_tr'))
                                        {
                                            if (count($current_node->field_city_tr))
                                            {
                                                $category_url_fragment = sab_oas_ads_get_term_current_url_fragment($current_node->field_city_tr[LANGUAGE_NONE][0]['tid']);
                                                if (!empty($category_url_fragment))
                                                {
                                                    $site_page_string = 'city/'.$category_url_fragment . '/';
                                                }
                                            }
                                        }

                                        $oas_site_page = 'studyabroad/' . $site_page_string;
                                        break;
                                }

                                break;
                            }
                        }
                    }
                }
                break;

            case 'taxonomy':
                $tid = $arguments[2];
                $existing_category_term = entity_load('taxonomy_term', array(
                    $tid
                ));

                if (count($existing_category_term) > 0)
                {
                    $current_category_term = $existing_category_term[$tid];
                    if (property_exists($current_category_term, 'vocabulary_machine_name'))
                    {
                        if (!empty($current_category_term->vocabulary_machine_name))
                        {
                            switch ($current_category_term->vocabulary_machine_name)
                            {
                                case 'article_categories':
                                    if (property_exists($current_category_term, 'field_legacy_external_id'))
                                    {
                                        if (count($current_category_term->field_legacy_external_id))
                                        {
                                            $oas_site_page = 'studyabroad';
                                        }
                                    }

                                    break;
                            }
                        }
                    }
                }
                break;
            default:
                $oas_site_page = 'studyabroad';

		}

        if(is_program_details_page()){

            $oas_site_page = 'studyabroad/program_detail_page';
        }
	}

	catch(Exception $e)
	{
		watchdog_exception('sab_oas_ads', $e);
	}
    if(empty($oas_site_page)){
        $oas_site_page ='studyabroad';
    }
	return $oas_site_page;
}

function sab_oas_ads_get_site_page_path_list()
{
    $results = array();
	try
	{


		// $product_list_nid_query = db_select('node', 'n')->fields('n', array('nid'));
		// $product_list_nids = $product_list_nid_query->execute()->fetchCol();
		// //dpm($product_list_nids);

		$product_list_nodes = node_load_multiple(array() , array(
			'type' => 'product_list'
		));
        $results = $product_list_nodes;
		//dpm(count($product_list_nodes));
	}

	catch(Exception $e)
	{
		//dpm($e);
		watchdog_exception('sab_oas_ads', $e);
	}

	return $results;
}

function sab_oas_ads_get_node_url_fragment($existing_node, $path_version)
{

	$oas_site_page = '';
    $site_page_string = '';
	try
	{
		if (!is_null($existing_node))
		{
			$current_node = $existing_node;
			if (!is_null($current_node))
			{
				if (property_exists($current_node, 'type'))
				{

					switch ($current_node->type)
					{
                        case 'product_list':
                        case 'aggregator_page':
                            $has_subject = false;
                            if (property_exists($current_node, 'field_category_tr'))
                            {
                                if (count($current_node->field_category_tr))
                                {
                                    $category_url_fragment = '';
                                    switch ($path_version)
                                    {
                                        case 'legacy':
                                            $category_url_fragment = sab_oas_ads_get_term_legacy_url_fragment($current_node->field_category_tr[LANGUAGE_NONE][0]['tid']);
                                            break;

                                        case 'current':
                                            $category_url_fragment = sab_oas_ads_get_term_current_url_fragment($current_node->field_category_tr[LANGUAGE_NONE][0]['tid']);
                                            break;
                                    }

                                    if (!empty($category_url_fragment))
                                    {
                                        $site_page_string.= $category_url_fragment . '/';
                                    }
                                }
                            }

                            if (property_exists($current_node, 'field_subject_tr'))
                            {
                                if (count($current_node->field_subject_tr))
                                {

                                    $subject_url_fragment = '';
                                    switch ($path_version)
                                    {
                                        case 'legacy':
                                            $subject_url_fragment = sab_oas_ads_get_term_legacy_url_fragment($current_node->field_subject_tr[LANGUAGE_NONE][0]['tid']);
                                            break;

                                        case 'current':
                                            $subject_url_fragment = sab_oas_ads_get_term_current_url_fragment($current_node->field_subject_tr[LANGUAGE_NONE][0]['tid']);
                                            break;
                                    }
                                    if (!empty($subject_url_fragment))
                                    {
                                        $site_page_string.= $subject_url_fragment . '/';
                                    }

                                    $has_subject = true;
                                }
                            }

                            if (property_exists($current_node, 'field_specialty_tr'))
                            {
                                if (count($current_node->field_specialty_tr))
                                {
                                    $specialty_url_fragment = '';
                                    switch ($path_version)
                                    {
                                        case 'legacy':
                                            $specialty_url_fragment = sab_oas_ads_get_term_legacy_url_fragment($current_node->field_specialty_tr[LANGUAGE_NONE][0]['tid']);
                                            break;

                                        case 'current':
                                            $specialty_url_fragment = sab_oas_ads_get_term_current_url_fragment($current_node->field_specialty_tr[LANGUAGE_NONE][0]['tid']);
                                            break;
                                    }
                                    if (!empty($specialty_url_fragment))
                                    {
                                        $site_page_string.= $specialty_url_fragment . '/';
                                    }

                                    $has_subject = true;
                                }
                            }

                            if ($has_subject)
                            {
                                $oas_site_page = 'studyabroad/two/subject/' . $site_page_string;
                            }
                            else
                            {
                                $oas_site_page = 'studyabroad/two/field/' . $site_page_string;
                            }

                            break;

                        case 'article_page':
                            $oas_site_page = 'studyabroad/resources';
                            break;
					}


				}
			}
		}
	}

	catch(Exception $e)
	{
		watchdog_exception('sab_oas_ads', $e);
	}

	return $oas_site_page;
}

function sab_oas_ads_get_term_legacy_url_fragment($tid)
{
	$legacy_url_fragment = '';
	try
	{
		$existing_category_term = entity_load('taxonomy_term', array(
			$tid
		));

		$current_category_term = $existing_category_term[$tid];

		if (property_exists($current_category_term, 'field_legacy_url_fragment'))
		{

			if (count($current_category_term->field_legacy_url_fragment))
			{
				$legacy_url_fragment = $current_category_term->field_legacy_url_fragment[LANGUAGE_NONE][0]['value'];
			}
		}
	}

	catch(Exception $e)
	{
		watchdog_exception('sab_oas_ads', $e);
	}

	return $legacy_url_fragment;
}

function sab_oas_ads_get_term_current_url_fragment($tid)
{
	$legacy_url_fragment = '';
	try
	{
		$existing_category_term = entity_load('taxonomy_term', array(
			$tid
		));

		$current_category_term = $existing_category_term[$tid];
		if (property_exists($current_category_term, 'name'))
		{
			if (count($current_category_term->name))
			{
				$legacy_url_fragment = _sab_oas_ads_format_as_machine_readable_string($current_category_term->name);
			}
		}
	}

	catch(Exception $e)
	{
		watchdog_exception('sab_oas_ads', $e);
	}

	return $legacy_url_fragment;
}
