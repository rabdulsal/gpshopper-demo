//
//  SCDateRangeFormatter.h
//  lunds
//
//  Created by kimberly on 8/31/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@protocol SCDateRangeFormatter < NSObject >

-(NSString *)stringFromDate: (NSDate *)d0
                     toDate: (NSDate *)d1;

@end


@interface SCFixedFormatDateRangeFormatter : NSObject < SCDateRangeFormatter >

@property (readonly) NSDateFormatter *startDateFormatter;
@property (readonly) NSDateFormatter *endDateFormatter;
@property (copy) NSString *format;

@end


@interface SCDeltaSpecificDateRangeFormatter : NSObject < SCDateRangeFormatter >

@property (retain) id<SCDateRangeFormatter> sameDayRangeFormatter;
@property (retain) id<SCDateRangeFormatter> sameMonthRangeFormatter;
@property (retain) id<SCDateRangeFormatter> sameYearRangeFormatter;
@property (retain) id<SCDateRangeFormatter> defaultRangeFormatter;
@property (readonly) NSDateFormatter *singleDateFormatter;
 
@end
