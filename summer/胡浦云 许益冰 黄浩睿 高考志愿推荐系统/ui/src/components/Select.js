import React from 'react';

export default function Select(props) {
  const options = Object.keys(props.options).map(key => (
    <option value={key} key={key} disabled={props.blackList && props.blackList.some(x => x == key) && 'disabled'}>
      {props.options[key]}
    </option>
  ));
  return (
    <select
      value={props.value}
      onChange={props.onChange}
    >
      {options}
    </select>
  );
}
