import pymunk


class BetterBody(pymunk.Body):
    def __init__(self, mass, inertia, body_type, parent):
        super(BetterBody, self).__init__(mass, inertia, body_type)
        self.parent = parent