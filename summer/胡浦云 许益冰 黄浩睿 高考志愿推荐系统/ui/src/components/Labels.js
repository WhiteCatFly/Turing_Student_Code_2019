import React from 'react';

export default function Labels(props) {
  return <ul className="labels">
    {
      props.data.map(label => <li className="label" key={label}>
        {label}
      </li>)
    }
  </ul>;
}
