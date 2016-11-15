/*
 * Copyright 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
/**
 * @interface
 */
WebInspector.TracingManagerClient = function() {};

WebInspector.TracingManagerClient.prototype = {
  tracingStarted: function() {},
  /**
   * @param {!Array.<!WebInspector.TracingManager.EventPayload>} events
   */
  traceEventsCollected: function(events) {},
  tracingComplete: function() {},
  /**
   * @param {number} usage
   */
  tracingBufferUsage: function(usage) {},
  /**
   * @param {number} progress
   */
  eventsRetrievalProgress: function(progress) {}
};

/**
 * @unrestricted
 */
WebInspector.TracingManager = class {
  /**
   * @param {!WebInspector.Target} target
   */
  constructor(target) {
    this._target = target;
    target.registerTracingDispatcher(new WebInspector.TracingDispatcher(this));

    /** @type {?WebInspector.TracingManagerClient} */
    this._activeClient = null;
    this._eventBufferSize = 0;
    this._eventsRetrieved = 0;
  }

  /**
   * @return {?WebInspector.Target}
   */
  target() {
    return this._target;
  }

  /**
   * @param {number=} usage
   * @param {number=} eventCount
   * @param {number=} percentFull
   */
  _bufferUsage(usage, eventCount, percentFull) {
    this._eventBufferSize = eventCount;
    this._activeClient.tracingBufferUsage(usage || percentFull || 0);
  }

  /**
   * @param {!Array.<!WebInspector.TracingManager.EventPayload>} events
   */
  _eventsCollected(events) {
    this._activeClient.traceEventsCollected(events);
    this._eventsRetrieved += events.length;
    if (!this._eventBufferSize)
      return;
    if (this._eventsRetrieved > this._eventBufferSize)
      this._eventsRetrieved = this._eventBufferSize;
    this._activeClient.eventsRetrievalProgress(this._eventsRetrieved / this._eventBufferSize);
  }

  _tracingComplete() {
    this._eventBufferSize = 0;
    this._eventsRetrieved = 0;
    this._activeClient.tracingComplete();
    this._activeClient = null;
    this._finishing = false;
  }

  /**
   * @param {!WebInspector.TracingManagerClient} client
   * @param {string} categoryFilter
   * @param {string} options
   * @param {function(?string)=} callback
   */
  start(client, categoryFilter, options, callback) {
    if (this._activeClient)
      throw new Error('Tracing is already started');
    var bufferUsageReportingIntervalMs = 500;
    this._activeClient = client;
    this._target.tracingAgent().start(
        categoryFilter, options, bufferUsageReportingIntervalMs, WebInspector.TracingManager.TransferMode.ReportEvents,
        callback);
    this._activeClient.tracingStarted();
  }

  stop() {
    if (!this._activeClient)
      throw new Error('Tracing is not started');
    if (this._finishing)
      throw new Error('Tracing is already being stopped');
    this._finishing = true;
    this._target.tracingAgent().end();
  }
};

/** @typedef {!{
        cat: string,
        pid: number,
        tid: number,
        ts: number,
        ph: string,
        name: string,
        args: !Object,
        dur: number,
        id: string,
        id2: (!{global: (string|undefined), local: (string|undefined)}|undefined),
        scope: string,
        bind_id: string,
        s: string
    }}
 */
WebInspector.TracingManager.EventPayload;

WebInspector.TracingManager.TransferMode = {
  ReportEvents: 'ReportEvents',
  ReturnAsStream: 'ReturnAsStream'
};

/**
 * @implements {TracingAgent.Dispatcher}
 * @unrestricted
 */
WebInspector.TracingDispatcher = class {
  /**
   * @param {!WebInspector.TracingManager} tracingManager
   */
  constructor(tracingManager) {
    this._tracingManager = tracingManager;
  }

  /**
   * @override
   * @param {number=} usage
   * @param {number=} eventCount
   * @param {number=} percentFull
   */
  bufferUsage(usage, eventCount, percentFull) {
    this._tracingManager._bufferUsage(usage, eventCount, percentFull);
  }

  /**
   * @override
   * @param {!Array.<!WebInspector.TracingManager.EventPayload>} data
   */
  dataCollected(data) {
    this._tracingManager._eventsCollected(data);
  }

  /**
   * @override
   */
  tracingComplete() {
    this._tracingManager._tracingComplete();
  }
};