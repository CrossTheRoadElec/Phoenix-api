#include "ctre/phoenix/motion/BufferedTrajectoryPointStream.h"
namespace ctre {
	namespace phoenix {
		namespace motion {
			BufferedTrajectoryPointStream::BufferedTrajectoryPointStream()
			{
				_handle = c_BuffTrajPointStream_Create1();
			}
			BufferedTrajectoryPointStream:: ~BufferedTrajectoryPointStream()
			{
				c_BuffTrajPointStream_Destroy(_handle);
				_handle = 0;
			}
			ctre::phoenix::ErrorCode BufferedTrajectoryPointStream::Clear()
			{
				return c_BuffTrajPointStream_Clear(_handle);
			}
			ctre::phoenix::ErrorCode BufferedTrajectoryPointStream::Write(const TrajectoryPoint & trajPt)
			{
				return c_BuffTrajPointStream_Write(_handle,
					trajPt.position,
					trajPt.velocity,
					trajPt.arbFeedFwd,
					trajPt.auxiliaryPos,
					trajPt.auxiliaryVel,
					trajPt.auxiliaryArbFeedFwd,
					trajPt.profileSlotSelect0,
					trajPt.profileSlotSelect1,
					trajPt.isLastPoint,
					trajPt.zeroPos,
					trajPt.timeDur,
					trajPt.useAuxPID);
			}
			ctre::phoenix::ErrorCode BufferedTrajectoryPointStream::Write(const TrajectoryPoint * trajPts, uint32_t trajPtCount)
			{
				ctre::phoenix::ErrorCode retval = OK;

				for (uint32_t i = 0; i < trajPtCount; ++i) {
					/* insert next pt */
					ctre::phoenix::ErrorCode er = Write(trajPts[i]);
					/* save first nonzero error code */
					if (retval == OK) { retval = er; }
				}

				return retval;
			}
		} // namespace motion
	} // namespace phoenix
} // namespace ctre
