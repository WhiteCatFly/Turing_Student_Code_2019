import React from 'react';

export default function Editor(props) {
  return (
    <input
      type={props.type || 'text'}
      min={props.min}
      max={props.max}
      value={props.value}
      pattern={props.pattern}
      onChange={props.onChange}
    />
  );
}
