from abc import ABC, abstractmethod


class GameObject(ABC):
    """
    Every object in the game derives from this GameObject base class
    """
    @abstractmethod
    def update(self):
        """
        Updating the object each frame
        """
        pass

    @abstractmethod
    def remove(self):
        """
        Cleaning up after when deleting an object
        """
        pass
