import React from 'react';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import {
  faExclamationTriangle,
  faExclamationCircle,
  faCheck
} from '@fortawesome/free-solid-svg-icons';
import * as ChartJS from 'react-chartjs-2';
import ChartJsPluginDataLabels from 'chartjs-plugin-datalabels';

import SchoolList from './data/schoolList';
import BadgeColors from './data/badgeColors';

import Labels from './components/Labels';

ChartJS.defaults.global.defaultFontFamily = '"Roboto", "Segoe UI", "Source Han Sans SC", "Microsoft Yahei UI", sans-serif';

class ResultListItem extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      expanded: false
    };

    this.transitionRunning = false;
  }

  onClick = () => {
    if (this.transitionRunning) return;
    this.transitionRunning = true;

    const expand = !this.state.expanded;
    this.setState({ expanded: !this.state.expanded });

    if (expand) {
      const animationFrame = () => {
        if (!this.transitionRunning) return;
        this.ref.scrollIntoViewIfNeeded();
        window.requestAnimationFrame(animationFrame);
      };
      animationFrame();  
    }

    const onTransitionEnd = e => {
      if (e.target == this.ref && e.propertyName === 'height') {
        this.transitionRunning = false;
        this.ref.removeEventListener('transitionend', onTransitionEnd);
      }
    };
    this.ref.addEventListener('transitionend', onTransitionEnd);
  }

  render() {
    const schoolInfo = SchoolList[this.props.schoolID];
    const badgeColor = `rgb(${BadgeColors[this.props.schoolID][0]}, ${BadgeColors[this.props.schoolID][1]}, ${BadgeColors[this.props.schoolID][2]})`;
    return <div
      className="list-item"
      data-expanded={!!this.state.expanded}
      ref={ref => this.ref = ref}
      onClick={this.onClick}
    >
      <div className="school-badge">
        <img src={`images/badges/${this.props.schoolID}.jpg`} alt={SchoolList[this.props.schoolID].name} />
      </div>
      <div className="school-name">
        {schoolInfo.name}
      </div>
      <Labels
        data={[
          schoolInfo.province_name,
          schoolInfo.city_name,
          schoolInfo.level_name,
          schoolInfo.type_name,
          schoolInfo.dual_class_name
        ].map(x => x.trim()).filter(x => x)}
      />
      {((type) => {
        if (type === '冲刺') return <div className="type 冲刺">
          <FontAwesomeIcon
            icon={faExclamationTriangle}
          />
          冲刺
          <span className="predicted-score">
            预测分数线：{this.props.predictScore}
          </span>
        </div>;
        else if (type === '稳健') return <div className="type 稳健">
          <FontAwesomeIcon
            icon={faExclamationCircle}
          />
          稳健
          <span className="predicted-score">
            预测分数线：{this.props.predictScore}
          </span>
        </div>;
        else if (type === '保底') return <div className="type 保底">
          <FontAwesomeIcon
            icon={faCheck}
          />
          保底
          <span className="predicted-score">
            预测分数线：{this.props.predictScore}
          </span>
        </div>;
      })(this.props.type)}
      <div
        className="former-scores-chart"
      >
        <ChartJS.Line
          options={{
            maintainAspectRatio: false,
            legend: {
              display: false
            },
            tooltips: {
              enabled: false
            },
            scales: {
              yAxes: [{
                ticks: {
                  suggestedMin: Math.min(...this.props.formerScores) - 20,
                  suggestedMax: Math.max(...this.props.formerScores) + 20,
                }
              }]
            },
            layout: {
              padding: {
                top: 10,
                right: 39
              }
            },
            plugins: {
              datalabels: {
                color: '#fff',
                backgroundColor: function(context) {
                  return context.dataset.backgroundColor;
                },
                padding: {
                  top: 3,
                  left: 4,
                  right: 4,
                  bottom: 1
                }
              }
            }  
          }}
          data={{
            labels: ['2014', '2015', '2016', '2017', '2018', '预测'],
            datasets: [{
              data: [...this.props.formerScores, this.props.predictScore].map(x => !x ? null : x),
              borderColor: badgeColor,
              backgroundColor: badgeColor,
              fill: false,  
              datalabels: {
                align: 'right',
                anchor: 'end',
                offset: 10,
                clamp: true
              }    
            }]
          }}
        />
      </div>
    </div>;
  }
}

export default function ResultPanel(props) {
  return <div
    className="result-panel"
  >
    {props.data.map((itemData, i) => <ResultListItem key={Math.random()} {...itemData} />)}
  </div>
}
