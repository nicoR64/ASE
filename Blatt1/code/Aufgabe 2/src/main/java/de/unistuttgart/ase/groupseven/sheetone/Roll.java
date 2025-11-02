package de.unistuttgart.ase.groupseven.sheetone;

/**
 * Immutable value object representing a single roll in the bowling game.
 *
 * @param pins the number of pins knocked down in this roll (0-{@link Frame#MAX_PINS})
 */
public record Roll(int pins) {}
