//
//  GPDEventsViewController.h
//  GPSDemo
//
//  Created by James Lee on 10/9/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GPDViewController.h"

@interface GPDEventsViewController : GPDViewController <SCEventsFetcherListener, UITableViewDataSource, UITableViewDelegate>

@end
