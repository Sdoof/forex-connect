#pragma once

/** Response listener class. */

class OrderMonitor;
class BatchOrderMonitor;

class ResponseListener : public IO2GResponseListener
{
 public:
    ResponseListener(IO2GSession *session);

    /** Increase reference counter. */
    virtual long addRef();

    /** Decrease reference counter. */
    virtual long release();

    /** Set request ID. */
    void setRequestID(const char *sRequestID);
    void setRequestIDs(std::vector<std::string> &requestIDs);

    /** Wait for request execution or error. */
    bool waitEvents();

    /** Get response.*/
    IO2GResponse *getResponse();

    /** Request execution completed data handler. */
    virtual void onRequestCompleted(const char *requestId, IO2GResponse *response = 0);

    /** Request execution failed data handler. */
    virtual void onRequestFailed(const char *requestId , const char *error);

    /** Request update data received data handler. */
    virtual void onTablesUpdates(IO2GResponse *data);

 private:
    volatile unsigned int mRefCount;
    /** Session object. */
    IO2GSession *mSession;
    /** Request we are waiting for. */
    std::string mRequestID;
    std::vector<std::string> mRequestIDs;
    /** Response Event handle. */
    HANDLE mResponseEvent;
    void printResult();
    void printOrderMonitor(OrderMonitor *monitor);
    void printTrades(std::vector<IO2GTradeRow*> &trades, std::string &sOrderID);
    void printClosedTrades(std::vector<IO2GClosedTradeRow*> &trades, std::string &sOrderID);
    BatchOrderMonitor *mBatchOrderMonitor;

    /** State of last request. */
    IO2GResponse *mResponse;
 protected:
    /** Destructor. */
    virtual ~ResponseListener();

};

