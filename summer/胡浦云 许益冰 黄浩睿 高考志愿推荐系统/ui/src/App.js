import React from 'react';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import {
  faComment
} from '@fortawesome/free-regular-svg-icons';
import {
  faSpinner
} from '@fortawesome/free-solid-svg-icons';
import * as request from 'request-promise';

import FormPanel from './FormPanel';
import ResultPanel from './ResultPanel';

// import mockResult from './data/mockResult';

export default class App extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      querying: false,
      resultData: [],
      welcome: true
    };
  }

  query = async formState => {
    if (this.state.querying) return;

    this.setState({
      querying: true,
      welcome: false
    });

    // query takes time
    // const resultData = await new Promise((res, rej) => setTimeout(() => res(mockResult), 500));

    let resultData;
    try {
      const result = JSON.parse(await request.post('http://127.0.0.1:8080', {
        body: JSON.stringify(formState)
      }));
  
      if (result.code === 1) {
        alert(`错误：${result.msg}`);
        window.require('electron').remote.app.exit();
      }

      resultData = result.data;
      console.log(result);
    } catch (e) {
      alert(e.toString());
      window.require('electron').remote.app.exit();
    }

    await this.preloadImages(resultData.map(item => `images/badges/${item.schoolID}.jpg`));
    this.setState({
      querying: false,
      resultData: resultData
    });
  }

  async preloadImages(urls) {
    return await Promise.all(urls.map(url => new Promise((res, rej) => {
      const img = new Image();
      img.onload = res;
      img.src = url;
    })));
  }

  bindTransitionEndEvent = elem => {
    // elem.addEventListener('transitionend', e => {
    //   console.log('transitionend fired', elem.style.opacity, e);
    //   if (e.target === elem && e.propertyName === 'opacity' && elem.style.opacity === 0) {
    //     elem.style.visibility = 'hidden';
    //   }
    // });

    // elem.addEventListener('transitionrun', e => {
    //   console.log('transitionrun fired', elem.style.opacity, e);
    //   if (e.target === elem && e.propertyName === 'opacity' && elem.style.opacity === 1) {
    //     elem.style.visibility = 'visible';
    //   }
    // });
  }

  render() {
    return (
      <div id="app">
        <div id="left-wrapper">
          <FormPanel onQuery={this.query} />
        </div>
        <div id="right-wrapper">
          <div className="right-layer" data-visible={true} ref={this.bindTransitionEndEvent}>
            <ResultPanel data={this.state.resultData} />
          </div>
          <div className="right-layer loading" data-visible={this.state.querying} ref={this.bindTransitionEndEvent}>
            <div className="centered-wrapper">
              <div className="centered">
                <FontAwesomeIcon style={{ animation: "fa-spin 2s infinite linear" }} icon={faSpinner} />
                <div>正在查询 …</div>
              </div>
            </div>
          </div>
          <div className="right-layer" data-visible={this.state.welcome} ref={this.bindTransitionEndEvent}>
            <div className="centered-wrapper">
              <div className="centered">
                <FontAwesomeIcon icon={faComment} />
                <div>请在左侧输入并查询</div>
              </div>
            </div>
          </div>
        </div>
      </div>
    );
  }
}
