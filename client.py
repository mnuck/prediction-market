#!/usr/bin/env python

from twisted.internet.defer import inlineCallbacks

from autobahn.twisted.util import sleep
from autobahn.twisted.wamp import ApplicationSession
from autobahn.wamp.exception import ApplicationError
from autobahn.twisted.wamp import ApplicationRunner


class AppSession(ApplicationSession):

    @inlineCallbacks
    def onJoin(self, details):
        prefix  = "com.nuckdev.prediction_market"

        def onMarket(market):
            print("Market Event: {}".format(market)

        def onOrder(order):
            print("Order Event: {}".format(order))

        def onParticipant(participant):
            print("Participant Event: {}".format(participant))

        yield self.subscribe(onMarket, prefix + ".market.feed")
        yield self.subscribe(onOrder, prefix + ".order.feed")
        yield self.subscribe(onParticipant, prefix + ".participant.feed")

        while True:
            yield sleep(1)
            ## CALL a remote procedure
            ##
"""        try:
            marketID = yield self.call(prefix + ".id")
            participantID = yield self.call(prefix + ".id")
            orderID = yield self.call(prefix + ".id")

            marketResult = yield self.call(prefix + ".market.open", marketID)
            print("Market result: {}".format(marketResult))

            participantResult = yield self.call(prefix + ".participant.open", participantID, 10000)
            print("Participant result: {}".format(participantResult))

            orderResult = yield self.call(prefix + ".order.open", orderID, participantID, marketID, 1, 1, 50)
            print("Order result: {}".format(orderResult))

                

        except ApplicationError as e:
            if e.error != 'wamp.error.no_such_procedure':
                raise e

            #yield sleep(1)
"""

runner = ApplicationRunner(url=u"ws://localhost:8080/ws", realm=u"realm1")
runner.run(AppSession)
