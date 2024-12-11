// Type definitions for electron-native-utils
// Project: electron-native-utils

interface NativeInput {
  /**
   * Perform a mouse click.
   *
   * Only supported on macOS.
   */
  click(options: { button: 'left' | 'right' }): void;

  /**
   * Set the mouse to the given position.
   *
   * Only supported on macOS.
   */
  setMousePosition(point: { x: number; y: number }): void;
}

export const nativeInput: NativeInput;
