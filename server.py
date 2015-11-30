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

        while True:
            yield self.publish(prefix + ".derp", [1, 2, [1, 2, {'a': 4}]])
            yield sleep(1)


runner = ApplicationRunner(url=u"ws://localhost:8080/ws", realm=u"realm1")
runner.run(AppSession)
