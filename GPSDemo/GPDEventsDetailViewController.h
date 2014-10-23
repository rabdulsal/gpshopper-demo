//
//  GPDEventsDetailViewController.h
//  GPSDemo
//
//  Created by James Lee on 10/9/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDViewController.h"
#import "TWTSideMenuViewController.h"
@import EventKit;
@import EventKitUI;

@interface GPDEventsDetailViewController : GPDViewController <CLLocationManagerDelegate, EKEventEditViewDelegate>

@property (strong, nonatomic) SCEvent *event;

@property (weak, nonatomic) IBOutlet UIImageView *imageView;
@property (weak, nonatomic) IBOutlet UILabel *titleLabel;
@property (weak, nonatomic) IBOutlet UILabel *detailLabel;
@property (weak, nonatomic) IBOutlet UILabel *addressLabel;

@end
