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
