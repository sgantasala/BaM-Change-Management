<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see bootstrap_preprocess_page()
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see bootstrap_process_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
?>
<header id="navbar" role="banner" class="<?php print $navbar_classes; ?> clearfix <?php if (template_is_program_details_page()): ?>program-details-page<?php endif; ?>">
    <div class="container">
        <div id="header-container" class="clearfix">

                <div id="header" class="clearfix">
                    <?php if ($page['use_site_header']): ?>
                        <?php if (!empty($page['header'])): ?>
                        <div id="header-ads" class="col-xs-6 col-xs-push-6">
                            <?php print render($page['header']); ?>
                        </div>
                        <?php endif;?>
                    <?php endif;?>
                    <div class="logo-container clearfix">
                        <?php if ($logo): ?>
                        <div id="logo" class="col-xs-6 col-xs-pull-6">
                            <div class="logo-wrapper">
                                <a class="logo navbar-btn" href="<?php print $front_page; ?>" title="<?php print t('StudyAbroad.com'); ?>">
                                    <?php
                        print theme_image(
				            array(
					            "path" => "$directory/images/sab-logo.png",
					            "attributes" => array(),
				            )
			            );
                                    ?>
                                </a>
                            </div>
                        </div>
                        <?php endif; ?>

                        <?php if ($page['use_site_header']): ?>
                            <!-- .btn-navbar is used as the toggle for collapsed navbar content -->
                            <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
                                <span class="sr-only">Toggle navigation</span>
                                <span class="icon-bar"></span>
                                <span class="icon-bar"></span>
                                <span class="icon-bar"></span>
                            </button>
                            <?php if (!empty($primary_nav) || !empty($page['navigation'])): ?>
                            <div id="header-menu">
                                <div class="navbar-collapse collapse">
                                    <nav role="navigation">
                                        <?php if (!empty($primary_nav)): ?>
                                        <?php print render($primary_nav); ?>
                                        <?php endif; ?>
                                        <?php if (!empty($page['navigation'])): ?>
                                        <?php print render($page['navigation']); ?>
                                        <?php endif; ?>
                                    </nav>
                                </div>
                            </div>
                            <?php endif; ?>
                        <?php endif; ?>
                    </div>
                    
                </div>

            
        </div>
    </div>
</header>

<div id="blank_slate_page" class="main-container container">

    <section class="col-sm-12 clearfix">
        <?php if (!empty($page['highlighted'])): ?>
        <div class="highlighted jumbotron">
            <?php print render($page['highlighted']); ?>
        </div>
        <?php endif; ?>
        <?php if (!empty($breadcrumb)): print $breadcrumb; endif;?>

        <?php print $messages; ?>
        <?php if (!empty($tabs)): ?>
        <?php print render($tabs); ?>
        <?php endif; ?>
        <?php if (!empty($page['help'])): ?>
        <?php print render($page['help']); ?>
        <?php endif; ?>
        <?php if (!empty($action_links)): ?>
        <ul class="action-links">
            <?php print render($action_links); ?>
        </ul>
        <?php endif; ?>

        <?php print render($page['content']); ?>

    </section>    

</div>

<?php if ($page['use_site_footer']): ?>
<footer id="footer" class="clearfix">

    <?php if (!empty($page['footer_column_one']) || !empty($page['footer_column_two']) || !empty($page['footer_column_three']) || !empty($page['footer_column_four'])): ?>
    <div class="footer-area clearfix">
        <div class="footer-area col-sm-2">
            <?php if (!empty($page['footer_column_one'])): ?>
            <?php print render($page['footer_column_one']);?>
            <?php endif;?>
        </div>
        <div class="footer-area col-sm-3">
            <?php if (!empty($page['footer_column_two'])): ?>
            <?php print render($page['footer_column_two']);?>
            <?php endif;?>
        </div>
        <div class="footer-area col-sm-3">
            <?php if (!empty($page['footer_column_three'])): ?>
            <?php print render($page['footer_column_three']);?>
            <?php endif;?>
        </div>
        <div class="footer-area col-sm-4">
            <?php if (!empty($page['footer_column_four'])): ?>
            <?php print render($page['footer_column_four']);?>
            <?php endif;?>
        </div>
    </div>
    <?php endif;?>
</footer>
<footer id="subfooter" class="text-center clearfix">
    <div class="footer-area clearfix">
        <?php if (!empty($page['subfooter'])): ?>
        <?php print render($page['subfooter']);?>
        <?php endif;?>
    </div>
</footer>
<?php endif;?>
