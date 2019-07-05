import React from 'react';
const pinyinlite = window.require('pinyinlite');

console.log(pinyinlite)

export default function GroupedSelect(props) {
  const items = Object.keys(props.options).map(key => ({
    leadingLetter: pinyinlite(props.options[key])[0][0][0].toUpperCase(),
    key: key,
    value: props.options[key]
  }));
  return (
    <select
      value={props.value}
      onChange={props.onChange}
    >
      {
         Object.keys(props.ungroupedOptions).map(key => (
          <option value={key} key={key} disabled={props.blackList && props.blackList.some(x => x == key) && 'disabled'}>
            {props.ungroupedOptions[key]}
          </option>
        ))
      }
      {
        Array.from(new Set(items.map(item => item.leadingLetter))).sort().map(letter => (
          <optgroup key={letter} label={letter}>
            {
              items.filter(item => item.leadingLetter === letter).map(item => (
                <option value={item.key} key={item.key} disabled={props.blackList && props.blackList.some(x => x == item.key) && 'disabled'}>
                  {props.options[item.value]}
                </option>
              ))
            }
          </optgroup>
        ))
      }
    </select>
  );
}
