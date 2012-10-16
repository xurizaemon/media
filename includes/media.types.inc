<?php

/**
 *  @file
 *  Helper functions related to media types.  CRUD for saving their settings mainly.
 *
 *  Also contains the media entity class definition.
 *  @see media.install for a list of the base types.
 */

/**
 * Implements hook_file_type_info_alter().
 */
function media_file_type_info_alter(array &$info) {
  // Add default view callback support for all file types.
  foreach ($info as $type => $type_info) {
    $info[$type] += array(
      'default view callback' => 'media_file_type_media_default_view',
    );
  }
}

/**
 * Implements hook_file_type_TYPE_default_view().
 *
 * Returns a drupal_render() array for displaying the file when there are no
 * administrator-configured formatters, or none of the configured ones return a
 * display.
 */
function media_file_type_media_default_view($file, $view_mode, $langcode) {
  // During preview, or when custom attribute values are needed on the displayed
  // element, use a media icon.
  if ($view_mode == 'preview' || isset($file->override)) {
    return array(
      '#theme' => 'media_formatter_large_icon',
      '#file' => $file,
    );
  }

  // Finally, fall back to File module's generic file display.
  return array(
    '#theme' => 'file_link',
    '#file' => $file,
  );
}

/**
 * Implements hook_file_default_displays().
 *
 * Provides default display configurations for media types.
 *
 * @see file_entity_schema()
 */
function media_file_default_displays() {
  $default_displays = array();

  $default_image_styles = array(
    'preview' => 'square_thumbnail',
    'teaser' => 'medium',
    'full' => 'large',
  );

  // For sites that updated from Media 1.x.
  // @see media_entity_info_alter()
  if (media_variable_get('show_deprecated_view_modes')) {
    $default_image_styles['media_original'] = '';
  }

  foreach ($default_image_styles as $view_mode => $image_style) {
    $display_name = 'image__' . $view_mode . '__file_image';
    $default_displays[$display_name] = (object) array(
      'api_version' => 1,
      'name' => $display_name,
      'status' => 1,
      'weight' => 5,
      'settings' => array('image_style' => $image_style),
    );
  }

  return $default_displays;
}
