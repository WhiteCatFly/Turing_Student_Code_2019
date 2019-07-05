import React from 'react';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import {
  faMapMarkedAlt,
  faSortAmountDown,
  faGraduationCap,
  faSchool,
  faSearch
} from '@fortawesome/free-solid-svg-icons';

import Editor from './components/Editor';
import Select from './components/Select';
import GroupedSelect from './components/GroupedSelect';
import Button from './components/Button';

import provinces from './data/provinces';
import majors from './data/majors';

function InputSection(props) {
  return (
    <div 
      className="input-section"
    >
      <div
        className="title"
      >
        {props.title}
      </div>
      <div>
        {props.input}
      </div>
    </div>
  );
}

export default class FormPanel extends React.Component {
  constructor(props) {
    super(props);

    this.state = {
      score: 0,
      province: 11, // 北京
      type: '理科',
      expectedMajor: '',
      rankOrScore: 'score',
      rank: 0
    };
  }

  onChangeProvince(provinceID) {
    this.setState({
      province: parseInt(provinceID)
    });

    if (!provinces[provinceID].types.includes(this.state.type)) {
      this.setState({
        type: provinces[provinceID].types[0]
      });
    }
  }

  isValidScore(text) {
    text = text.replace(/^0+/, '');
    return text.length === 0 || (parseInt(text) > 0 && parseInt(text).toString() === text);
  }

  render() {
    const provincesList = {}, provincesBlackList = [];
    for (const id in provinces) {
      provincesList[id] = provinces[id].name;
      if (provinces[id].types.length === 0) provincesBlackList.push(id);
    }

    const majorsList = {};
    for (const major of majors) {
      majorsList[major] = major;
    }

    const typeOptions = {};
    for (const type of provinces[this.state.province].types) {
      typeOptions[type] = type;
    }

    return <div
      className="form-panel"
    >
      <InputSection
        title={
          <span>
            <FontAwesomeIcon
              icon={faMapMarkedAlt}
            />
            省份
          </span>
        }
        input={
          <Select
            options={provincesList}
            onChange={e => this.onChangeProvince(e.target.value)}
            value={this.state.province}
            blackList={provincesBlackList}
          />
        }
      />
      <InputSection
        title={
          <span>
            <FontAwesomeIcon
              icon={faSortAmountDown}
            />
            <span
              className="switch-span-selected"
            >分数</span>
          </span>
        }
        input={
          <Editor
            min="0"
            type="number"
            onChange={e => this.isValidScore(e.target.value) && this.setState({ score: parseInt(e.target.value) })}
            value={this.state.score.toString()}
          />
        }
      />
      <InputSection
        title={
          <span>
            <FontAwesomeIcon
              icon={faGraduationCap}
            />
            类别
          </span>
        }
        input={
          <Select
            options={typeOptions}
            onChange={e => this.setState({ type: e.target.value })}
            value={this.state.type}
          />
        }
      />
      <InputSection
        title={
          <span>
            <FontAwesomeIcon
              icon={faSchool}
            />
            期望专业
          </span>
        }
        input={
          <GroupedSelect
            ungroupedOptions={{ '': '未指定' }}
            options={majorsList}
            onChange={e => this.setState({ expectedMajor: e.target.value })}
            value={this.state.expectedMajor}
          />
        }
      />
      <div
        className="button-section"
      >
        <Button
          title={
            <span>
              <FontAwesomeIcon
                icon={faSearch}
              />
              查询
            </span>
          }
          onClick={() => this.props.onQuery(this.state)}
        />
      </div>
    </div>;
  }
}
